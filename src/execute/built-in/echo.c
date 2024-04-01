/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:20:19 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/01 15:52:00 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_is_flag(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		i = 2;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	else
		return (false);
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (ft_is_flag(args[i]) == true)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] && args[i][0])
			ft_printf(" ");
		i++;
	}
	if (flag == 0)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
