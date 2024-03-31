/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:57:42 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/31 19:50:45 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_here_doc(char *delimiter, int i, t_prompt *prompt)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (exec_error(".here_doc", strerror(errno),
				errno, prompt->process[i]->pid), -1);
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

static	int	set_infile(t_lst_infile *infile, int i, t_prompt *prompt)
{
	int	fd;
	int	tmp_in;

	tmp_in = dup(STDIN_FILENO);
	if (infile && infile->here_doc)
	{	
		dup2(tmp_in, STDIN_FILENO);
		fd = handle_here_doc(infile->name, i, prompt);
	}
	else
		fd = open(infile->name, O_RDONLY);
	close(tmp_in);
	if (fd == -1)
		return (exec_error(infile->name, strerror(errno),
				errno, prompt->process[i]->pid));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

void	ft_set_pipes(t_prompt *prompt, int i)
{
	if (i != 0)
	{
		dup2(prompt->last_pipe_fd, STDIN_FILENO);
		close(prompt->process[i - 1]->fd[0]);
		close(prompt->last_pipe_fd);
	}
	if (i != prompt->process_count - 1)
	{
		dup2(prompt->process[i]->fd[1], STDOUT_FILENO);
		close(prompt->process[i]->fd[1]);
	}
	close(prompt->process[i]->fd[0]);
}

int	ft_set_files(t_prompt *prompt, int i)
{
	int					fd;
	t_lst_infile		*infile;
	t_lst_outfile		*outfile;

	infile = prompt->process[i]->infile;
	while (infile)
	{
		if (set_infile(infile, i, prompt))
			return (errno);
		infile = infile->next;
	}
	outfile = prompt->process[i]->outfile;
	while (outfile)
	{
		fd = open(outfile->name, outfile->append_mode, 0644);
		if (fd == -1)
			return (exec_error(outfile->name, strerror(errno),
					errno, prompt->process[i]->pid));
		dup2(fd, STDOUT_FILENO);
		close(fd);
		outfile = outfile->next;
	}
	return (EXIT_SUCCESS);
}
