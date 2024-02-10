/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:09:45 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 13:25:56 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// initializing all variable of the minishell scope
//envp is a constant to be able to modify it if required during the execution it is duplicated into not const char *

static char **duplicate_environment(char **envp, t_shell *shell)
{
    int i = 0;
    int j = 0;
    char **env_copy;
    
    while (envp[i])
        i++;
    env_copy = safe_malloc(sizeof(char *) * (i + 1), shell);
    while (j < i) 
    {
        env_copy[j] = strdup(envp[j]);
        if (!env_copy[j]) 
        {
            ft_freetab(env_copy);
            return (NULL); 
        }
        j++;
    }
    env_copy[j] = NULL;
    return (env_copy);
}

void init_shell(t_shell **shell, char **envp)
{
    *shell = safe_malloc(sizeof(t_shell), *shell);
    (*shell)->env = duplicate_environment(envp, *shell);
    //if (!shell->env) = env dup failure or env -i
    (*shell)->prompt = NULL;
    (*shell)->exit = false;
    (*shell)->exit_status = 0;
    (*shell)->pid = 0;
    (*shell)->sigquit = 0;
    (*shell)->sigint = 0;
}

