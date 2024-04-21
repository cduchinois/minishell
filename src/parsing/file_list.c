/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:28:30 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 19:41:50 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_file	*create_file_node(const char *filename, int type, \
							int mode, t_shell *shell)
{
	t_lst_file	*node;

	node = (t_lst_file *)safe_malloc(sizeof(t_lst_file), shell);
	node->name = strdup(filename);
	node->type = type;
	node->mode = mode;
	node->next = NULL;
	return (node);
}

void	append_file_node(t_lst_file **head, t_lst_file *new_node)
{
	t_lst_file	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	infile_init(t_list **current, t_lst_file **head, \
					t_process *process, t_shell *shell)
{
	t_lst_file	*new_node;
	int			mode;

	if (ft_strcmp((*current)->content, "<<") == 0)
		mode = 1;
	else
		mode = 0;
	new_node = create_file_node((*current)->next->content, \
								0, mode, shell);
	if (new_node)
		append_file_node(head, new_node);
	*current = (*current)->next->next;
	process->argc -= 2;
}

void	outfile_init(t_list **current, t_lst_file **head, \
					t_process *process, t_shell *shell)
{
	t_lst_file	*new_node;
	int			mode;

	if (strcmp((*current)->content, ">>") == 0)
		mode = O_WRONLY | O_CREAT | O_APPEND;
	else
		mode = O_WRONLY | O_CREAT | O_TRUNC;
	new_node = create_file_node((*current)->next->content, \
											1, mode, shell);
	if (new_node)
		append_file_node(head, new_node);
	*current = (*current)->next->next;
	process->argc -= 2;
}

t_lst_file	*file_list_init(t_list *start, t_process *process, t_shell *shell)
{
	t_lst_file (*head) = NULL;
	t_list (*current) = start;
	while (current && current->next && strcmp(current->content, "|") != 0)
	{
		if (strcmp(current->content, "<") == 0 || \
		strcmp(current->content, "<<") == 0)
			infile_init(&current, &head, process, shell);
		else if (strcmp(current->content, ">") == 0 || \
		strcmp(current->content, ">>") == 0)
			outfile_init(&current, &head, process, shell);
		else
			current = current->next;
	}
	return (head);
}
