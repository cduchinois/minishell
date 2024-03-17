
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


int	handle_here_doc(char *delimiter, int i)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd_infile, line, ft_strlen(line));
		free(line);
	}
	close(fd_infile);
	return (open(".here_doc", O_RDONLY));
}

void set_fd(t_prompt *prompt, int i)
{
	t_lst_infile *infile;
	t_lst_outfile *outfile;
	int fd;
	int tmp_in;

	infile = prompt->process[i]->infile;
	tmp_in = dup(STDIN_FILENO);
	while (infile)
	{
		if (infile && infile->here_doc)
		{	
			dup2(tmp_in, STDIN_FILENO);
			fd = handle_here_doc(infile->name, i);
		}
		else
			fd = open(infile->name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		infile = infile->next;
	}
	outfile = prompt->process[i]->outfile;
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
	if (prompt->process[i]->command)
	{
		ft_exec_process(prompt->process[i]);
		if (!ft_is_builtin(prompt->process[i]->command))
		{
			perror("exec_process");
			exit(EXIT_FAILURE);
		}
	}
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

void ft_execute(t_prompt *prompt) {
    int i;
    int j;
    int prev_read = -1;
    int pipe_fds[2];
	int std_backup[2];

	std_backup[0]= dup(STDIN_FILENO);
    std_backup[1]= dup(STDOUT_FILENO);

    if (prompt->process_count == 1 && prompt->process[0]->command && ft_strcmp(prompt->process[0]->command, "exit") == 0)
        ft_exit(prompt->process[0]);
    for (i = 0; i < prompt->process_count; i++)
	{
        if (prompt->process[i]->command && ft_is_builtin(prompt->process[i]->command) && i == prompt->process_count - 1)
            ft_child(prompt, i);
        else 
		{
            if (pipe(pipe_fds) < 0) 
			{
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            prompt->process[i]->pid = fork();
            if (prompt->process[i]->pid < 0)
			{
                perror("fork");
                exit(EXIT_FAILURE);
            }
			else if (prompt->process[i]->pid == 0) 
			{
                if (i != 0)
				{
                    dup2(prev_read, STDIN_FILENO);
                    close(prev_read);
                }
                if (i != prompt->process_count - 1) {
                    dup2(pipe_fds[1], STDOUT_FILENO);
                }
                close(pipe_fds[0]);
                close(pipe_fds[1]);
                ft_child(prompt, i);
                exit(EXIT_SUCCESS);
            } 
			else
			{
                if (prev_read != -1)
                    close(prev_read);
                prev_read = pipe_fds[0];
                close(pipe_fds[1]);
            }
        }
    }
    for (i = 0; i < prompt->process_count; i++)
        waitpid(prompt->process[i]->pid, NULL, 0);
    dup2(std_backup[0], STDIN_FILENO);
    dup2(std_backup[1], STDOUT_FILENO);
    close(std_backup[0]);
    close(std_backup[1]);
	unlink(".here_doc");
}