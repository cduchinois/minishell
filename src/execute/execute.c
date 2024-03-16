
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

void set_fd(t_prompt *prompt, int i)
{
	t_lst_infile *infile;
	t_lst_outfile *outfile;
	int fd;

	infile = prompt->process[i]->infile;
	if (i > 0)
		dup2(prompt->process[i - 1]->fd[0], STDIN_FILENO);
	while (infile)
	{
		fd = open(infile->name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		infile = infile->next;
	}
	outfile = prompt->process[i]->outfile;
	if (i < prompt->process_count - 1)
		dup2(prompt->process[i]->fd[1], STDOUT_FILENO);
	while (outfile)
	{
		fd = open(outfile->name, outfile->append_mode, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		outfile = outfile->next;
	}
}

void ft_child(t_prompt *prompt, int i)
{
	int j;

	j = 0;
	set_fd(prompt, i);
	while(j <= i) 
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
        ft_exit(prompt->process[i]);
	ft_set_pipes(prompt);
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
