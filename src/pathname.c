/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:39:25 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 07:25:00 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**find_path_from_envp(char **envp, const char *var_name)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0)
		{
			path = ft_split((envp[i] + ft_strlen(var_name) + 1), ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_first_word(char *str)
{
	int		i;
	int		len;
	char	*first_word;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	len = i;
	first_word = malloc(len + 1);
	if (!first_word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		first_word[i] = str[i];
		i++;
	}
	first_word[i] = '\0';
	return (first_word);
}

char	*create_full_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*get_pathname(char **env, char *command)
{
	char	*pathname;
	char	**path;
	
	if (!command)
		return (NULL);
	path = find_path_from_envp(env, "PATH");
	if (!path)
	{
		if (access(command, F_OK & X_OK) == 0)
			return (command);
	}
	while (*path)
	{
		pathname = create_full_path(*path, command);
		if (pathname && access(pathname, F_OK | X_OK) == 0)
		{
			free(command);
			ft_freetab(path);
			return (pathname);
		}
		free(pathname);
		path++;
	}
	ft_freetab(path);
	free(command);
	return (NULL);
}
