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

/*
    built in env that prints the env variable with no options and no ARGUMENTS
*/

int ft_env(char **env,int argc)
{
    int i;

    i = 0;
    if (argc > 0)
        return (EXIT_FAILURE); //To do : ERROR MANAGEMENT too many arguments
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}