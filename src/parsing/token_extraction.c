/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 11:28:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_isquote(char s) 
{
    if (!s)
        return 0;
    return (s == '\'' || s == '\"');
}
int find_start(char *input, int *index, bool *in_squote, bool *in_dquote) 
{
    while (input[*index])
    {
        if (!*in_squote && !*in_dquote && input[*index] == ' ')
        {
            (*index)++;
        }
        else if (!*in_squote && !*in_dquote && ft_isquote(input[*index]) == 1)
        {
            if (input[*index] == '\'')
                *in_squote = true;
            else 
                *in_dquote = true;
            (*index)++;
            return (*index);
        }
        else 
            return (*index);
    }
    return -1;
}

int handle_unquoted(char *input, int *index, bool *firstIteration) 
{
    if (input[*index] == ' ') {
        return 1; // Indicates that find_end should return *index
    } else if (input[*index] == '|' || input[*index] == '<' || input[*index] == '>') {
        if (*firstIteration) {
            *firstIteration = false;
            if (input[*index] == '|') {
                (*index)++;
            } else { // Covers both '<' and '>'
                *index += ft_redirlen(input + *index);
            }
        }
        return 1;
    }
    return 0;
}

int find_end(char *input, int *index, bool *squote, bool *dquote)
{
    bool firstIteration = true;
    
    while (input[*index])
    {
        if (!*squote && !*dquote)
        {
            if (handle_unquoted(input, index, &firstIteration))
                return *index;
        }
        if ((*squote && input[*index] == '\'') || (*dquote && input[*index] == '\"')) {
            *squote = false;
            *dquote = false;
            (*index)++;
            if (!*squote && !*dquote)
                return *index - 1;
        }
        else 
        {
            firstIteration = false;
            (*index)++;
        }
    }
    return *index;
}

char *extract_token(char *input, int *index, t_shell *shell)
{
    bool was_in_single_quote;
    
    bool (squote) = false;
    bool (dquote) = false;
    int start = find_start(input, index, &squote, &dquote);
    if (start == -1)
        return NULL;
    was_in_single_quote = squote;
    int end = find_end(input, index, &squote, &dquote);
    if (start < end) 
    {
        char *token = ft_strndup(input + start, end - start);
        if (!(ft_strchr(token, '$') || was_in_single_quote))
            return token;
        else 
        {
            char *expanded_token = ft_expand_token(token, shell);
            free(token);
            return expanded_token;
        }
    }
    return NULL;
}
