/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 15:16:06 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int find_start(char *input, int *index, bool *in_squote, bool *in_dquote)
{
    while (input[*index])
    {
        if (!*in_squote && !*in_dquote && (input[*index] == ' ' || input[*index] == '\t'))
            (*index)++;
        else if (!*in_squote && !*in_dquote && ft_isquote(input[*index]) == 1)
        {
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

int	handle_unquoted(char *input, int *index, bool *firstIteration)
{
	if (input[*index] == ' ')
		return (1);
	else if (input[*index] == '|' || input[*index] == '<' \
			|| input[*index] == '>')
	{
		if (*firstIteration)
		{
			*firstIteration = false;
			if (input[*index] == '|')
				(*index)++;
			else
				*index += ft_redirlen(input + *index);
		}
		return (1);
	}
	return (0);
}	

int	find_end(char *input, int *index, bool *squote, bool *dquote)
{
	bool (firstIteration) = true;
	while (input[*index])
	{
		if (!*squote && !*dquote)
		{
			if (handle_unquoted(input, index, &firstIteration))
				return (*index);
		}
		if ((*squote && input[*index] == '\'') || \
			(*dquote && input[*index] == '\"'))
		{
			*squote = false;
			*dquote = false;
			(*index)++;
			if (!*squote && !*dquote)
				return (*index - 1);
		}
		else
		{
			firstIteration = false;
			(*index)++;
		}
	}
	return (*index);
}

t_list *extract_token(char *input, int *index, t_shell *shell)
{
    bool was_in_single_quote = false, was_in_double_quote = false;
    int start = find_start(input, index, &was_in_single_quote, &was_in_double_quote);
    if (start == -1) return NULL;
    // printf("start_i:%d\n", *index);

    int end = find_end(input, index, &was_in_single_quote, &was_in_double_quote);
        // printf("end_i:%d\n", *index);
    if (start < end)
    {
        char *token_str = ft_strndup(input + start, end - start);
        if (!(was_in_double_quote || was_in_single_quote))
            trim_quote(&token_str);
        t_list *token = safe_malloc(sizeof(t_list), shell);
        token->content = token_str;
        // printf("token_str: %s\n", token->content);
        if (ft_strchr(token_str, '$') && !was_in_single_quote)
            token->content = ft_expand_token(token_str, shell);
        if (ft_strchr(token_str, '*') && !was_in_single_quote && !was_in_double_quote)
        {
            t_list *token_lst = handle_wildcard(token_str, shell);
            free(token);
            return token_lst;
        }
        return token;
    }
    else
        return NULL;
}
