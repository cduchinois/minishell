/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:38:11 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 13:08:52 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exec_error(char *cmd, char *msg, int error, int ex)
{
    ft_putstr_fd("minishell :", 2);

    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);    
    if (ex == 0 && error == EFAULT)
        exit(127);
    if (ex == 0) {
        exit(error);
    }
    g_signal = error;
    return (error);
}

int exec_error2(t_process *process, char *msg, int error, int ex)
{
    ft_putstr_fd("minishell :", 2);
    ft_putstr_fd((process)->args[0], 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
  
    ft_clear_fd(process->prompt);
    ft_free_env(process->shell->env);
    free(process->shell);
    free_prompt(process->prompt);
    if (ex == 0 && error == EFAULT)
    {
        exit(127);
    }
    if (ex == 0) {
        exit(error);
    }
    g_signal = error;
    return (error);
}

