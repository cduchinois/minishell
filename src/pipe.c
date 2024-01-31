/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:56:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:37:21 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_here_doc(char *deliminator)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, deliminator, ft_strlen(deliminator) == 0))
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

int handle_infile(char *infile, int here_doc)
{
    if (here_doc) 
	{
        return handle_here_doc(infile);
    } 
	else 
	{
        int fd = open(infile, O_RDONLY);
        return fd;
    }
}

void ft_fd_in(int i, t_process **processes)
{
    int fd_infile;
    if (processes[i]->infile) 
	{
        fd_infile = handle_infile(processes[i]->infile, processes[i]->here_doc);
        if (fd_infile < 0) 
		{
            perror("Error opening infile");
            exit(EXIT_FAILURE);
        }
		dup2(fd_infile, STDIN_FILENO);
		if (i == 0) 
			close(fd_infile); 
		else
		{
			close(processes[i - 1]->fd[0]);
			close(processes[i - 1]->fd[1]);
	   	}
	}
	else
	{
		if (i > 0) 
		{
			dup2(processes[i - 1]->fd[0], STDIN_FILENO);
			close(processes[i - 1]->fd[0]);
			close(processes[i - 1]->fd[1]);
	   	}
	}
}

void ft_fd_out(int i, t_process **processes, int process_count)
{
    int fd_outfile;
    if (processes[i]->outfile) 
	{
        int flags = O_WRONLY | O_CREAT;
        if (processes[i]->append_mode)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;
        fd_outfile = open(processes[i]->outfile, flags, 0644);
        if (fd_outfile < 0) 
		{
            perror("Error opening outfile");
            exit(EXIT_FAILURE);
        }
        dup2(fd_outfile, STDOUT_FILENO);
        close(fd_outfile);
    } 
	else if (i < process_count - 1) 
	{
        dup2(processes[i]->fd[1], STDOUT_FILENO);
        close(processes[i]->fd[0]);
        close(processes[i]->fd[1]);
    } 
	else 
	{
        dup2(STDOUT_FILENO, STDOUT_FILENO); // Redundant but for clarity
    }
}
