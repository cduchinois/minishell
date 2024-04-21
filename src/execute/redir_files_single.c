/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir files single.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:57:42 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 16:51:28 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	set_infile_bt(t_lst_file *file, int i, t_prompt *prompt)
{
	int	fd;
	int	tmp_in;

	tmp_in = dup(STDIN_FILENO);
	if (tmp_in == -1)
		return (exec_error2(prompt->process[i], strerror(errno),
				errno, prompt->process[i]->pid));
	if (file->mode == 1)
		fd = handle_here_doc(file->name, i, prompt);
	else
		fd = open(file->name, O_RDONLY);
	if (fd == -1)
	{
		close(tmp_in);
		return (exec_error2(prompt->process[i], strerror(errno),
				errno, prompt->process[i]->pid));
	}
	close(tmp_in);
	return (EXIT_SUCCESS);
}

static int	set_outfile_bt(t_lst_file *file, int i, t_prompt *prompt)
{
	int	fd;

	fd = open(file->name, file->mode, 0644);
	if (fd == -1)
	{
		exec_error2(prompt->process[i], strerror(errno),
			1, prompt->process[i]->pid);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_set_files_bt(t_prompt *prompt, int i)
{
	t_lst_file	*file;

	file = prompt->process[i]->file;
	while (file)
	{
		if (file->type == 0)
		{
			if (set_infile_bt(file, i, prompt) != EXIT_SUCCESS)
				return (1);
		}
		else if (file->type == 1)
		{
			if (set_outfile_bt(file, i, prompt) != EXIT_SUCCESS)
				return (1);
		}
		file = file->next;
	}
	return (EXIT_SUCCESS);
}
