/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:38:11 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 02:13:50 by yuewang          ###   ########.fr       */
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

int exec_error2(t_process **process, char *msg, int error, int ex)
{
    ft_putstr_fd("minishell :", 2);
    ft_putstr_fd((*process)->args[0], 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
  
    if ((*process)->prompt->token)
        ft_freelst((*process)->prompt->token); 
    if((*process)->args)
        ft_freetab((*process)->args);
    if((*process)->file)
        free_file_list((*process)->file);
    free((*process)->prompt);
    free((*process)->shell);
    free((*process));
    free(process);
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

