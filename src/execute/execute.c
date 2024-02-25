/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 07:04:22 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void set_file(t_prompt *prompt, int file)
{
	t_lst_infile *infile;
	t_lst_outfile *outfile;
	int fd;

	if (file == STDIN_FILENO)
	{
		infile = prompt->process[0]->infile;
		while (infile)
		{
			 fd = open(infile->name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			infile = infile->next;
		};
	}
	else if (file == STDOUT_FILENO)
	{
		outfile = prompt->process[prompt->process_count - 1]->outfile;
		while (outfile)
		{
			fd = open(outfile->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			outfile = outfile->next;
		}
	}
}

void ft_child(t_prompt *prompt, int i)
{
	int j;

	j = 0;
	if (i > 0)
		dup2(prompt->process[i - 1]->fd[0], STDIN_FILENO);
	else if (i == 0)
		set_file(prompt, STDIN_FILENO);
	if (i < prompt->process_count - 1)
	{
		dup2(prompt->process[i]->fd[1], STDOUT_FILENO);
	}
	else if (i == prompt->process_count - 1)
		set_file(prompt, STDOUT_FILENO);
	while(j <= prompt->process_count) 
	{
		close(prompt->process[j]->fd[0]);
		close(prompt->process[j]->fd[1]);
		j++;
	}
	ft_exec_process(prompt->process[i]);
	perror("exec_process");
	exit(EXIT_FAILURE);
}

void ft_set_pipes(t_prompt *prompt)
{
	int i;

	i = 0;
    while (i < prompt->process_count)
	{
        if (pipe(prompt->process[i]->fd) == -1)
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		i++;
    }
}
void ft_execute(t_prompt *prompt)
{
    int i;
	int j;

    i = 0;
    if (prompt->process_count == 1 && ft_strcmp(prompt->process[0]->command, "exit") == 0)
        exit(0);
	ft_set_pipes(prompt);
	print_prompt(prompt);
    while (i < prompt->process_count)
    {
		j = 0;
        prompt->process[i]->pid = fork();
        if (prompt->process[i]->pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (prompt->process[i]->pid == 0)
            ft_child(prompt, i);
        waitpid(prompt->process[i]->pid, &prompt->last_exit, 0);    
        while(j <= i)
		{
			if (i != j)
				close(prompt->process[j]->fd[0]);
			close(prompt->process[j]->fd[1]);
			j++;
		}
        i++;
    }
	close(prompt->process[i - 1]->fd[0]);
}
