/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:56:25 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 13:42:30 by fgranger         ###   ########.fr       */
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

void clean_shell(t_shell *shell)
{
	ft_free_env(shell->env);	
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
	if (process->shell->exit_status == 0)
		process->shell->exit_status = last_exit;
	// printf("exit status updated ft_execbt:%d\n", process->shell->exit_status);
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


void ft_exec_process(t_process *process)
{
    char *path;
    char **env_tab;
    struct stat file_stat;

    if (ft_is_builtin(process->command))
    {
        ft_exec_builtin(process);
        // printf("is exit status updated:%d\n", process->shell->exit_status);
    }
    else
    {
        env_tab = rebuild_env(process->shell->env);
        path = get_pathname(process->shell->env, process->command, process);
		if (path == NULL) // Check if path is NULL
        {
			ft_freetab(env_tab);
			ft_free_env(process->shell->env);
			ft_clear_fd(process->prompt);
            exec_error2(process, "command not found", 127, process->pid);
        }
        if (execve(path, process->args, env_tab) == -1)
        {
            ft_freetab(env_tab);
			ft_free_env(process->shell->env);
            exec_error2(process, "command not found", 127, process->pid);
            // exit(127); // 127 for command not found
        }
        ft_freetab(env_tab);
		ft_free_env(process->shell->env);
		exit(EXIT_SUCCESS);
	}
	// ft_freetab(env_tab);
	// ft_free_env(process->shell->env);
}

void ft_exec_process2(t_process **process, int i)
{
    char *path;
    char **env_tab;
    struct stat file_stat;

    if (ft_is_builtin(process[i]->command))
        ft_exec_builtin(process[i]);	
    else
    {
        env_tab = rebuild_env(process[i]->shell->env);
        path = get_pathname(process[i]->shell->env, process[i]->command, process[i]);
		if (path == NULL) // Check if path is NULL
        {
			ft_freetab(env_tab);
            exec_error2(process[i], "command not found", 127, process[i]->pid);
        }
        if (execve(path, process[i]->args, env_tab) == -1)
        {
            ft_freetab(env_tab);
            exec_error2(process[i], "command not found", 127, process[i]->pid);
            // exit(127); // 127 for command not found
        }
        ft_freetab(env_tab);
		ft_clear_fd(process[i]->prompt);
    	ft_free_env(process[i]->shell->env);
    	free(process[i]->shell);
    	free_prompt(process[i]->prompt);
		exit(EXIT_SUCCESS);
	}
}


