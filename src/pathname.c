/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:39:25 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 17:15:09 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_var_from_envp(t_lst_env *env, char *var_name)
{
	char	*varible;
	
	while (env)
    {
        if (ft_strncmp(env->key, var_name, ft_strlen(var_name)) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
	return (NULL);
}

t_lst_env *find_path_from_envp(t_lst_env *env_list, const char *var_name)
{
    while (env_list)
    {
        if (ft_strncmp(env_list->key, var_name, strlen(var_name)) == 0) {
            return env_list;
        }
        env_list = env_list->next;
    }
    return NULL;
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

char *get_pathname(t_lst_env *env, char *command)
{
    char    *pathname = NULL;
    t_lst_env *path_env;
    char    **path;
    char    *found_pathname = NULL;

    if (!command) return (NULL);
    if (access(command, F_OK | X_OK) == 0)
        return (command);
    path_env = find_path_from_envp(env, "PATH");
    if (!path_env || !(path_env->value))
    {
        if (access(command, F_OK | X_OK) == 0)
            return (command);
        else {
            free(command);
            return (NULL);
        }
    }
    path = ft_split(path_env->value, ':');
    if (!path) {
        free(command);
        return NULL;
    }

    for (int i = 0; path[i] && !found_pathname; i++)
    {
        pathname = create_full_path(path[i], command);
        if (pathname && access(pathname, F_OK | X_OK) == 0) {
            found_pathname = pathname;
        } else {
            free(pathname);
        }
    }

    ft_freetab(path);

    if (found_pathname)
    {
        return found_pathname;
    } else {
        return NULL;
    }
}


