/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:45 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/17 19:55:47 by fgranger         ###   ########.fr       */
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
	if (!process)
		return (EXIT_FAILURE);
	if (process->argc < 2)
		exit(process->shell->exit_status);
	if (ft_is_valid_exit(process->args[1]) == EXIT_FAILURE)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		exit(2);
	}
	else if (process->argc > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	exit (ft_atoi(process->args[1]));
}
