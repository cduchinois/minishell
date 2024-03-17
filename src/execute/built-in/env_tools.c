/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:55:55 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/17 19:56:48 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	key = malloc(sizeof(char *) * i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_lst_env	*var_exist(t_lst_env *env, char *var)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_get_key(var);
	if (!key)
		return (NULL);
	while (env)
	{
		if (env->key && ft_strcmp(env->key, key) == 0)
			return (free(key), env);
		i++;
		env = env->next;
	}
	free(key);
	return (NULL);
}

int	var_is_valid(char *var, int mode)
{
	int	i;

	i = 1;
	if (!var)
		return (UNVALID);
	if (ft_isalpha(var[0]) == 0 && var[0] != '_' || !ft_strcmp(var, "_"))
		return (UNVALID);
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (!var[i])
		return (EMPTY);
	if (mode == 0 && var[i] != '=')
		return (UNVALID);
	if (mode == 1 && var[i] == '=')
		return (UNVALID);
	i++;
	while (var[i] && ft_isprint(var[i]))
		i++;
	if (!var[i])
		return (VALID);
	return (UNVALID);
}

int	ft_env_len(t_lst_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}
