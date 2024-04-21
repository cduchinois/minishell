/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:42:58 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 19:30:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> // For directory manipulation
#include <fnmatch.h> // For wildcard pattern matching
#include <string.h> // For strdup

DIR	*open_directory(char *path)
{
	DIR (*dir) = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	return (dir);
}

t_list	*handle_wildcard(char *token_str, t_shell *shell)
{
	struct dirent	*entry;
	t_list			*new;

	t_list (*head) = NULL;
	t_list (*current) = head;
	DIR (*dir) = open_directory(".");
	if (!dir)
		return (NULL);
	while (entry == readdir(dir) && entry != NULL)
	{
		if (fnmatch(token_str, entry->d_name, 0) == 0 && \
					entry->d_name[0] != '.')
		{
			new = safe_malloc(sizeof(t_list), shell);
			new->content = strdup(entry->d_name);
			new->next = NULL;
			if (head == NULL)
				head = new;
			else
				current->next = new;
			current = new;
		}
	}
	closedir(dir);
	return (head);
}
