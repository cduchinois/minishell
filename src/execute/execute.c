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

static void ft_exec_builtin(t_process *process)
{
	
	if (ft_strcmp(process->command, "echo") == 0)
		process->prompt->last_exit = ft_echo(process->args);
	else if (ft_strcmp(process->command, "pwd") == 0)
		process->prompt->last_exit = ft_pwd();
	else if (ft_strcmp(process->command, "env") == 0)
		process->prompt->last_exit = ft_env(process->shell->env, 0);
	exit(process->prompt->last_exit);
}

static bool ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	//other buit-ins to be added later on
	return (false);
}

static void ft_exec_process(t_process *process)
{
	char *path;
	
    if (ft_is_builtin(process->command) == true)
		ft_exec_builtin(process);
	else
	{
		ft_printf("test");
		path = get_pathname(process->shell->env, process->command);
		ft_printf("%s", path);
		execve(path, process->args, process->shell->env);
	}
}

void	ft_execute(t_prompt *prompt)
{
	int i;
	
	i = 0;
	if (prompt->process_count == 1 && ft_strcmp(prompt->process[0]->command, "exit") == 0)
		exit(0); // exit function builtin to code ;
	while (i < prompt->process_count)
	{
		prompt->process[i]->pid = fork();
		if (prompt->process[i]->pid < 0)
		{
			//error_handle
		}
		else if (prompt->process[i]->pid == 0)
		{
			//to do ft_pipe for redirections (including check if in or outfile and open function if appropriate)
			ft_exec_process(prompt->process[i]);
			perror("exec_process");
            exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(prompt->process[i]->pid, &prompt->last_exit, 0);
			i++;
		}
	}
}
