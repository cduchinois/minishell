
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
			exit(127);
		}
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
    {
		ft_exit(prompt->process[0]);
		return ;
	}
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
        waitpid(prompt->process[i]->pid, &prompt->shell->exit_status, 0);
	if (prompt->shell->exit_status & 0x7F)
		prompt->shell->exit_status = prompt->shell->exit_status & 0x7F;
	else
		prompt->shell->exit_status = (prompt->shell->exit_status >> 8) & 0xFF;
    dup2(std_backup[0], STDIN_FILENO);
    dup2(std_backup[1], STDOUT_FILENO);
    close(std_backup[0]);
    close(std_backup[1]);
	unlink(".here_doc");
}