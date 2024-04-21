/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:38:11 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 14:42:22 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int exec_error2(t_process *process, char *msg, int error, int ex)
{
    ft_putstr_fd("minishell :", 2);
    ft_putstr_fd((process)->args[0], 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
  

    if (ex == 0 && error == EFAULT)
    {
        ft_clear_fd(process->prompt);
        ft_free_env(process->shell->env);
        free(process->shell);
        free_prompt(process->prompt);
        exit(127);
    }
    if (ex == 0) {
        ft_clear_fd(process->prompt);
        ft_free_env(process->shell->env);
        free(process->shell);
        free_prompt(process->prompt);
        exit(error);
    }
    g_signal = error;
    return (error);
}

