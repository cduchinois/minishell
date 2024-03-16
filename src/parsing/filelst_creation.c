/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filelst_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:28:30 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 17:51:40 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_infile *create_infile_node(const char *filename, bool here_doc, t_shell *shell)
{
    t_lst_infile *node = (t_lst_infile *)safe_malloc(sizeof(t_lst_infile), shell);
    node->name = strdup(filename);
    node->here_doc = here_doc;
    node->next = NULL;
    return node;
}

void append_infile_node(t_lst_infile **head, t_lst_infile *new_node)
{
    if (!head || !new_node) return;

    if (*head == NULL)
    {
        *head = new_node;
    } 
    else 
    {
        t_lst_infile *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

t_lst_outfile *create_outfile_node(const char *filename, int append_mode, t_shell *shell)
{
    t_lst_outfile *node = (t_lst_outfile *)safe_malloc(sizeof(t_lst_outfile), shell);
    node->name = strdup(filename);
    node->append_mode = append_mode;
    node->next = NULL;
    return node;
}

void append_outfile_node(t_lst_outfile **head, t_lst_outfile *new_node) 
{
    if (!head || !new_node) return;

    if (*head == NULL)
    {
        *head = new_node;
    } 
    else
    {
        t_lst_outfile *current = *head;
        while (current->next) 
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

