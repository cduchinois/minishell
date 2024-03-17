/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:09:45 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 15:28:21 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// initializing all variable of the minishell scope
//envp is a constant to be able to modify it if required during the execution it is duplicated into not const char *

t_lst_env *env_new_node(char *key, const char *value, bool export_only, t_shell *shell)
{
    t_lst_env *node = safe_malloc(sizeof(t_lst_env), shell);
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->export_only = export_only;
    node->next = NULL;
    return node;
}

void env_append(t_lst_env **lst, t_lst_env *new_node)
{
    if (!lst || !new_node) return;
    if (!*lst) 
    {
        *lst = new_node;
    }
    else
    {
        t_lst_env *last = *lst;
        while (last->next != NULL)
            last = last->next;
        last->next = new_node;
    }
}

t_lst_env *duplicate_environment(char **envp, t_shell *shell)
{
    t_lst_env *env_list = NULL;
    int i = 0;
    while (envp[i])
    {
        char *env_var = envp[i];
        char *separator = ft_strchr(env_var, '=');
        if (separator)
        {
            *separator = '\0';
            t_lst_env *new_node = env_new_node(env_var, separator + 1, false, shell);
            env_append(&env_list, new_node);
            *separator = '=';
        }
        i++;
    }
    return env_list;
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
//     (*shell)->sigquit = 0;
//     (*shell)->sigint = 0;
}

