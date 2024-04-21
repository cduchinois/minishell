/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:45 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 12:52:31 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_is_valid_exit(char *num)
{
	int	i;

	i = 0;
	if (!num)
		return (EXIT_FAILURE);
	while (num[i] == ' ' || (num[i] >= 9 && num[i] <= 13))
		i++;
	if (num[i] == '-' || num[i] == '+')
		i++;
	if (!ft_isdigit(num[i]))
		return (EXIT_FAILURE);
    if (!num[i]) // If only a sign is present without digits, it's an error
        return (EXIT_FAILURE);
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_process *process)
{
	int ex;

	ex = process->shell->exit_status;

	if (!process)
		return (EXIT_FAILURE);
	if (process->argc < 2)
	{
		ft_clear_fd(process->prompt);
		ft_free_env(process->shell->env);
		free(process->shell);
		free_prompt(process->prompt);
		exit(ex);
	}
	if (ft_is_valid_exit(process->args[1]) == EXIT_FAILURE)
	{
		exec_error("exit", "numeric argument required", 2, process->pid);
		process->shell->exit_status = 2;
        return (EXIT_FAILURE);
	}
	else if (process->argc > 2)
	{
		// ft_putendl_fd("exit", 2);
		exec_error("exit", "too many arguments", 1, process->pid);
		process->shell->exit_status = 1;
		return (EXIT_FAILURE);
	}
	ex = ft_atoi(process->args[1]);
	ft_clear_fd(process->prompt);
	ft_free_env(process->shell->env);
	free(process->shell);
	free_prompt(process->prompt);
	exit (ex);
}
