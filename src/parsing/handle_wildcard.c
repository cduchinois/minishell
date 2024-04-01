/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:42:58 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 15:15:35 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h> // For directory manipulation
#include <fnmatch.h> // For wildcard pattern matching
#include <string.h> // For strdup

t_list *handle_wildcard(char *token_str, t_shell *shell)
{
    DIR *dir;
    struct dirent *entry;
    t_list *head = NULL, *current = head;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (fnmatch(token_str, entry->d_name, 0) == 0)
        {
            t_list *new = safe_malloc(sizeof(t_list), shell);
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
    return head;
}