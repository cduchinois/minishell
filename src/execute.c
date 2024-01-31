/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:58:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:32:56 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void ft_execve(char **env, t_process *process) {
    char *const *exec_arg;  // Use 'char *const *' instead of 'const char **'

    if (!process->pathname) {
        char *sh_args[] = {"/bin/sh", "-c", *process->args, NULL}; // Assuming process->args[0] is the command
        exec_arg = sh_args;
        execve("/bin/sh", exec_arg, env);
    } else {
        execve(process->pathname, process->args, env);
    }
    perror("execve failed");
    exit(1);
}

void	ft_execute(t_shell *shell)
{
	int i = 0;

	if (shell->process_count == 1)
		ft_execve(shell->env, shell->processes[0]);
	while (i < shell->process_count)
	{
		shell->pid[i] = fork();
		if (shell->pid[i] < 0)
		{
			//error_handle
		}
		else if (shell->pid[i] == 0)
		{
			ft_execve(shell->env, shell->processes[i]);
			exit(1);
		}
		else
		{
			if (i > 0)
				close(shell->processes[i - 1]->fd[0]);
			if (i < shell->process_count - 1)
				close(shell->processes[i]->fd[1]);
		}
		i++;
	}
}
