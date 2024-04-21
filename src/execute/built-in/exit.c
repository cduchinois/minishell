/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:45 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 16:41:44 by fgranger         ###   ########.fr       */
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
	if (!num[i])
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
	int	ex;

	if (!process)
		return (EXIT_FAILURE);
	if (process->argc < 2)
	{
		clear_sub(process);
		exit(g_signal);
	}
	if (ft_is_valid_exit(process->args[1]) == EXIT_FAILURE)
	{
		ft_putendl_fd("Exit : numeric argument required", 2);
		g_signal = 2;
		return (EXIT_FAILURE);
	}
	else if (process->argc > 2)
	{
		ft_putendl_fd("Exit : too many arguments", 2);
		g_signal = 1;
		return (EXIT_FAILURE);
	}
	ex = ft_atoi(process->args[1]);
	clear_sub(process);
	exit (ex);
}
