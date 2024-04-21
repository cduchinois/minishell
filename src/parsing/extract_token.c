/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 16:11:04 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int find_start(char *input, int *index, bool *in_squote, bool *in_dquote)
{
    while (input[*index])
    {
                // printf("Current char: %c, Index: %d, In single quote: %d, In double quote: %d\n", input[*index], *index, *in_squote, *in_dquote);
    
        if (!*in_squote && !*in_dquote && (input[*index] == ' ' || input[*index] == '\t'))
        {    (*index)++;
        }
        else if (!*in_squote && !*in_dquote && ft_isquote(input[*index]) == 1)
        {
                        // printf("Quote found at index %d\n", *index); // Additional debug print

            if (input[*index] == '\'')
                *in_squote = true;
            else if (input[*index] == '"')
                *in_dquote = true;
            (*index)++;
            break ;
        }
        else
            break ;
    }
    if (input[*index] == '\0')
        return (-1);
    return (*index);
}

int find_end(char *input, int *index, bool *squote, bool *dquote)
{
    bool quoted = false;
    if (*squote || *dquote)
        quoted = true;
    if (quoted == false && (input[*index] == '|' || input[*index] == '<' || input[*index] == '>'))
    {
        
        if (input[*index] == '|')
            (*index)++;
        else 
        {
            int len = ft_redirlen(input + *index);
            // printf("len:%d\n", len);
            *index += len;
        }
        return *index;   
    }
    while (input[*index])
    {
        if (!*squote && !*dquote)
        {
            if (input[*index] == ' ')
                return (*index);
            else if (input[*index] == '|' || input[*index] == '<' || input[*index] == '>')
                return *index;   
            else if (input[*index] == '\'')
                *squote = true;
            else if (input[*index] == '"')
                *dquote = true;
            (*index)++;
        }
        else if ((*squote && input[*index] == '\'') || (*dquote && input[*index] == '"'))
        {
            *squote = false;
            *dquote = false;
            (*index)++;
            if (quoted == true && (!input[*index] || input[*index] == ' ' || input[*index] == '\t')) // Check if the index is still within bounds
                return (*index - 1);
        }
        else
        {
            (*index)++;
            if (!input[*index]) // Prevent going past the null terminator
                break;
        }
    }
    return (*index);
}

// void trim_list(t_list **head)
// {
//     t_list *current = *head;
//     t_list *prev = NULL;

//     while (current != NULL)
//     {
//         if (current->content == NULL || current->content == " ")
//         {
//             t_list *temp = current;
//             if (prev == NULL)
//             {
//                 *head = current->next;
//             }
//             else
//             {
//                 prev->next = current->next;
//             }
//             current = current->next;
//             free(temp->content);
//             free(temp);
//         }
//         else
//         {
//             prev = current;
//             current = current->next;
//         }
//     }
// }

t_list *extract_token(char *input, int *index, t_shell *shell)
{
    bool was_in_single_quote = false, was_in_double_quote = false;
    bool in_squote = false, in_dquote = false;

    int start = find_start(input, index, &in_squote, &in_dquote);
    if (start == -1) return NULL;
    was_in_single_quote = in_squote;
    was_in_double_quote = in_dquote;
    int end = find_end(input, index, &in_squote, &in_dquote);
    
    if (start < end || was_in_double_quote || was_in_single_quote)
    {
        char *token_str = ft_strndup(input + start, end - start + 1);
        if (!(was_in_double_quote || was_in_single_quote)) 
        {
            token_str = trim_quote(token_str);
        }
        else if (was_in_double_quote && ft_strchr(token_str, '"')) {
            token_str = remove_quotes(token_str, '"');
        }
        else if (was_in_single_quote && ft_strchr(token_str, '\'')) {
            token_str = remove_quotes(token_str, '\'');
        }
        if (strchr(token_str, '$') && !was_in_single_quote) {
            char *expanded_token = ft_expand_token(token_str, shell);
            free(token_str);
            token_str = expanded_token;
        }
        if (strchr(token_str, '*') && !was_in_single_quote && !was_in_double_quote) {
            t_list *token_lst = handle_wildcard(token_str, shell);
            free(token_str);
            return NULL;
        }
        if (token_str[0] == '\0' && !(was_in_double_quote || was_in_single_quote)) {
            free(token_str);
            return NULL;
        }

        t_list *token = safe_malloc(sizeof(t_list), shell);
        ft_memset(token, 0, sizeof(t_list));
        token->content = token_str;
        return token;
    }
    return NULL;
}
