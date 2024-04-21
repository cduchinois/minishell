/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:56:14 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/17 19:56:15 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	void	swap_nodes(t_lst_env *current)
{
	char	*tmp[2];

	tmp[0] = current->key;
	tmp[1] = current->value;
	current->key = current->next->key;
	current->value = current->next->value;
	current->next->key = tmp[0];
	current->next->value = tmp[1];
}

static	t_lst_env	*ft_sort_env(t_lst_env *env, int len, t_shell *shell)
{
	int			i;
	int			j;
	t_lst_env	*current;
	t_lst_env	*new_env;

	new_env = ft_env_dup(env, shell);
	i = 0;
	while (i < len - 1)
	{
		current = new_env;
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
				swap_nodes(current);
			j++;
			current = current->next;
		}
		i++;
	}
	return (new_env);
}

t_lst_env	*ft_env_dup(t_lst_env *env, t_shell *shell)
{
	t_lst_env	*dup;
	t_lst_env	*new;

	dup = NULL;
	new = NULL;
	while (env)
	{
		new = env_new_node(env->key, env->value, env->export_only, shell);
		if (!new)
			return (NULL);
		env_append(&dup, new);
		env = env->next;
	}
	return (dup);
}

int	ft_print_sorted_env(t_lst_env *env, t_shell *shell)
{
	int			len;
	t_lst_env	*new_env;

	len = ft_env_len(env);
	new_env = ft_sort_env(env, len, shell);
	while (new_env != NULL)
	{
		if (strcmp(new_env->key, "_"))
			ft_printf("declare -x %s=\"%s\"\n", new_env->key, new_env->value);
		new_env = new_env->next;
	}
	ft_free_env(new_env);
	return (EXIT_SUCCESS);
}
