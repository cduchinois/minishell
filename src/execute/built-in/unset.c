/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:56:21 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/23 19:56:34 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	delete_var(t_lst_env **env, char *var)
{
	t_lst_env	*current;
	t_lst_env	*tmp;

	current = *env;
	if (*env == NULL)
		return (EXIT_FAILURE);
	if (!strcmp((*env)->key, var))
	{
		*env = (*env)->next;
		free(current->key);
		free(current->value);
		free(current);
		return (EXIT_SUCCESS);
	}
	while (current->next != NULL && strcmp(current->next->key, var))
		current = current->next;
	if (current->next != NULL)
	{
		tmp = current->next;
		current->next = current->next->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return (EXIT_SUCCESS);
}

int	unset_var(t_process *process, char *var)
{
	int	input_status;

	input_status = var_is_valid(var, 1);
	if (input_status == UNVALID)
		return (EXIT_FAILURE);
	else if (var_exist(process->shell->env, var))
		return (delete_var(&process->shell->env, var));
	return (EXIT_FAILURE);
}

int	unset_vars(t_process *process)
{
	int		i;
	bool	error;

	i = 1;
	error = false;
	while (process->args[i])
	{
		error += unset_var(process, process->args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_process *process)
{
	if (process->argc == 1)
		return (EXIT_SUCCESS);
	else
		return (unset_vars(process));
	return (EXIT_SUCCESS);
}
