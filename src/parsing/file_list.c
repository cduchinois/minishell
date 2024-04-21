/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:28:30 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/18 19:02:08 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



// t_lst_outfile	*create_outfile_node(const char *filename, \
// 				int append_mode, t_shell *shell)
// {
// 	t_lst_outfile	*node;

// 	node = (t_lst_outfile *)safe_malloc(sizeof(t_lst_outfile), shell);
// 	node->name = strdup(filename);
// 	node->append_mode = append_mode;
// 	node->next = NULL;
// 	return (node);
// }

// void	append_outfile_node(t_lst_outfile **head, t_lst_outfile *new_node)
// {
// 	t_lst_outfile	*current;

// 	if (!head || !new_node)
// 		return ;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 	}
// 	else
// 	{	
// 		current = *head;
// 		while (current->next)
// 		{
// 			current = current->next;
// 		}
// 		current->next = new_node;
// 	}
// }
