/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:30 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 15:30:38 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	update_var(t_lst_env *env, char *var, int status)
{
	char		*value;
	t_lst_env	*to_update;

	if (status == VALID)
	{
		value = strdup(ft_strchr(var, '=') + 1);
		to_update = var_exist(env, var);
		if (to_update->value)
			free(to_update->value);
		to_update->value = value;
	}
	else
	{
		to_update = var_exist(env, var);
		if (to_update->value)
			free(to_update->value);
		to_update->value = ft_strdup("");
	}
	to_update->export_only = false;
	return (EXIT_SUCCESS);
}

int	add_var(t_lst_env *env, char *var, int status, t_shell *shell)
{
	char		*value;
	char		*key;
	t_lst_env	*new;

	if (!env || !var || !shell)
		return (EXIT_FAILURE);
	key = ft_get_key(var);
	value = NULL;
	if (status == VALID)
	{
		value = strdup(ft_strchr(var, '=') + 1);
		new = env_new_node(key, value, false, shell);
	}
	else
	{
		value = strdup("");
		new = env_new_node(key, value, true, shell);
	}
	env_append(&env, new);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}

int	export_var(t_shell *shell, char *var)
{
	int	input_status;

	input_status = var_is_valid(var, 0);
	if (input_status == UNVALID)
	{
		ft_putstr_fd(" not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	else if (var_exist(shell->env, var))
		return (update_var(shell->env, var, input_status));
	else
		return (add_var(shell->env, var, input_status, shell));
	return (EXIT_FAILURE);
}

int	export_vars(t_process *process)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (process->args[i])
	{
		error += export_var(process->shell, process->args[i]);
		i++;
	}
	if (error == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export(t_process *process)
{
	if (process->argc == 1)
		return (ft_print_sorted_env(process->shell->env, process->shell));
	else
		return (export_vars(process));
	return (EXIT_SUCCESS);
}
