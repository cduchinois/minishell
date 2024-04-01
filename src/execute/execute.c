/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 17:01:57 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signal;

void	get_status(int sig)
{
	if (g_signal <= 131 && g_signal >= 130)
		return ;
	if (sig & 0x7F)
		g_signal = sig & 0x7F;
	else
		g_signal = (sig >> 8) & 0xFF;
}

void	ft_child(t_prompt *prompt, int i)
{
	ft_set_pipes(prompt, i);
	if (ft_set_files(prompt, i))
		return ;
	if (prompt->process[i]->command)
		ft_exec_process(prompt->process[i]);
}

void	ft_fork(t_prompt *prompt, int i)
{
	if (pipe(prompt->process[i]->fd) < 0)
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
		ft_child(prompt, i);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (prompt->last_pipe_fd != -1)
			close(prompt->last_pipe_fd);
		prompt->last_pipe_fd = prompt->process[i]->fd[0];
		close(prompt->process[i]->fd[1]);
	}
}

void	ft_clear_fd(t_prompt *prompt, int sub)
{
	int i = 0;

	while(i < prompt->process_count)
	{
		if (prompt->process[i]->fd[0] > 0)
			close(prompt->process[i]->fd[0]);
		if (prompt->process[i]->fd[1] > 0)
			close(prompt->process[i]->fd[1]);
		i++;
	}
	if (sub == 0)
	{
		dup2(prompt->backup_fd[0], STDIN_FILENO);
		dup2(prompt->backup_fd[1], STDOUT_FILENO);
	}
	close(prompt->backup_fd[0]);
	close(prompt->backup_fd[1]);
	unlink(".here_doc");
}

int	ft_execute(t_prompt *prompt)
{
	int	i;
	int	sig;

	i = -1;
	prompt->backup_fd[0] = dup(STDIN_FILENO);
	prompt->backup_fd[1] = dup(STDOUT_FILENO);
	prompt->last_pipe_fd = -1;
	if (prompt->process_count == 1 && prompt->process[0]->command
		&& ft_strcmp(prompt->process[0]->command, "exit") == 0)
		return (ft_exit(prompt->process[0]), EXIT_FAILURE);
	while (++i < prompt->process_count)
	{
		if (prompt->process[i]->command && i == prompt->process_count - 1
			&& ft_is_builtin(prompt->process[i]->command))
			ft_child(prompt, i);
		else
		{
			ft_fork(prompt, i);
			waitpid(prompt->process[i]->pid, &sig, 0);
			get_status(sig);
		}
	}
	ft_clear_fd(prompt, 0);
	return (EXIT_SUCCESS);
}
