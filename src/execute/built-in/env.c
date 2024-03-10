/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:19:40 by fgranger          #+#    #+#             */
/*   Updated: 2024/02/04 21:25:53 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_env(char **env,int argc)
{
    int i;

    i = 0;
    if (argc > 0)
        return (ft_putendl_fd("Too many arguments",2), EXIT_FAILURE);
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}