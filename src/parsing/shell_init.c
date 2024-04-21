/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:09:45 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/19 21:38:06 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_env	*env_new_node(char *key, const char *value, \
			bool export_only, t_shell *shell)
{
	t_lst_env	*node;

	node = safe_malloc(sizeof(t_lst_env), shell);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->export_only = export_only;
	node->next = NULL;
	return (node);
}

void	env_append(t_lst_env **lst, t_lst_env *new_node)
{
	t_lst_env	*last;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
	}
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

t_lst_env	*duplicate_environment(char **envp, t_shell *shell)
{
	t_lst_env	*new_node;
	char		*env_var;
	char		*separator;
	int			i;

	i = 0;
	t_lst_env (*env_list) = NULL;
	while (envp[i])
	{
		env_var = envp[i];
		separator = ft_strchr(env_var, '=');
		if (separator)
		{
			*separator = '\0';
			new_node = env_new_node(env_var, separator + 1, false, shell);
			env_append(&env_list, new_node);
			*separator = '=';
		}
		i++;
	}
	new_node = env_new_node("_", "./minishell", false, shell);
	env_append(&env_list, new_node);
	return (env_list);
}

void	init_shell(t_shell **shell, char **envp)
{
	*shell = safe_malloc(sizeof(t_shell), *shell);
	(*shell)->env = duplicate_environment(envp, *shell);
	(*shell)->prompt = NULL;
	(*shell)->exit = false;
	(*shell)->exit_status = 0;
	(*shell)->pid = 0;
}
