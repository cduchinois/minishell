/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 14:38:13 by fgranger         ###   ########.fr       */
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
    {
        exit(EXIT_FAILURE);
    }
	if (prompt->process[i]->command)
		ft_exec_process2(prompt->process, i);
    ft_clear_fd(prompt->process[i]->prompt);
    ft_free_env(prompt->process[i]->shell->env);
    free(prompt->process[i]->shell);
    free_prompt(prompt->process[i]->prompt);
}

void	ft_fork(t_prompt *prompt, int i)
{
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
        // Parent process
        if (prompt->last_pipe_fd != -1)
            close(prompt->last_pipe_fd);
        prompt->last_pipe_fd = prompt->shell->fd[0];
        close(prompt->shell->fd[1]);
    }
}
void	ft_clear_fd(t_prompt *prompt)
{
	dup2(prompt->backup_fd[0], STDIN_FILENO);
	dup2(prompt->backup_fd[1], STDOUT_FILENO);
	close(prompt->backup_fd[0]);
	close(prompt->backup_fd[1]);
	unlink(".here_doc");
}

int ft_execute(t_prompt *prompt)
{
    int i;
    int sig;
    i = -1;
    prompt->last_pipe_fd = -1;

    if (prompt->process_count == 1 && prompt->process[0]->command
        && ft_strcmp(prompt->process[0]->command, "exit") == 0)
        return(ft_exit(prompt->process[0]));

    if (prompt->process_count == 1 && prompt->process[0]->command 
		&& ft_is_builtin(prompt->process[0]->command))
    {
        if (ft_set_files_bt(prompt, 0) != EXIT_SUCCESS)
            prompt->shell->exit_status = 1;
        else
            ft_exec_builtin(prompt->process[0]);
        ft_clear_fd(prompt);
        return (0);
    }

    while (++i < prompt->process_count)
    { 
        pipe(prompt->shell->fd);
        ft_fork(prompt, i);
    }
    
    i = -1;
    while (++i < prompt->process_count)
    {
        if (waitpid(prompt->process[i]->pid, &sig, 0) == -1)
        {
            perror("waitpid");
            return (0);
        }		
		if (WIFEXITED(sig)) {
			prompt->shell->exit_status = WEXITSTATUS(sig);
        } else if (WIFSIGNALED(sig)) {
			prompt->shell->exit_status = WTERMSIG(sig);
        }
    }
    
    close(prompt->shell->fd[0]);
    ft_clear_fd(prompt);
}
