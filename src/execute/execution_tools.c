/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:56:25 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 16:40:10 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**rebuild_env(t_lst_env *env)
{
	t_lst_env	*tmp;
	int			len;
	char		**env_tab;
	int			i;
	char		*buffer;

	len = ft_env_len(env);
	env_tab = malloc(sizeof(char *) * (len + 1));
	if (!env_tab)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		buffer = ft_strjoin(tmp->key, "=");
		env_tab[i] = ft_strjoin(buffer, tmp->value);
		free(buffer);
		tmp = tmp->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	ft_exec_builtin(t_process *process)
{
	int	last_exit;

	if (ft_strcmp(process->command, "echo") == 0)
		last_exit = ft_echo(process->args);
	else if (ft_strcmp(process->command, "pwd") == 0)
		last_exit = ft_pwd();
	else if (ft_strcmp(process->command, "env") == 0)
		last_exit = ft_env(process->shell->env, process->argc - 1);
	else if (ft_strcmp(process->command, "export") == 0)
		last_exit = ft_export(process);
	else if (ft_strcmp(process->command, "unset") == 0)
		last_exit = ft_unset(process);
	else if (ft_strcmp(process->command, "cd") == 0)
		last_exit = ft_cd(process);
	if (process->pid == 0)
	{
		ft_clear_fd(process->prompt);
		ft_free_env(process->shell->env);
		free(process->shell);
		free_prompt(process->prompt);
		exit(last_exit);
	}
	g_signal = last_exit;
}

bool	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	return (false);
}

void	ft_exec_process(t_process *process)
{
	char		*path;
	char		**env_tab;

	if (ft_is_builtin(process->command))
		ft_exec_builtin(process);
	else
	{
		path = get_pathname(process->shell->env, process->command, process);
		env_tab = rebuild_env(process->shell->env);
		if (path == NULL)
		{
			ft_freetab(env_tab);
			exec_error2(process, "command not found", 127, process->pid);
		}
		if (execve(path, process->args, env_tab) == -1)
		{
			ft_freetab(env_tab);
			free(path);
			exec_error2(process, "command not found", 127, process->pid);
		}
		ft_freetab(env_tab);
		free(path);
		clear_sub(process);
		exit(EXIT_SUCCESS);
	}
}
