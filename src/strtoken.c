/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:25:54 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int update_quote_state(char quote, int *in_single_quote, int *in_double_quote)
{
	if (quote == '\'')
	{
		//what does this mean?
		*in_single_quote = !*in_single_quote;
		return *in_double_quote == 0;
	}
	else if (quote == '\"')
	{
		*in_double_quote = !*in_double_quote;
		return *in_single_quote == 0;
	}
	return 0;
}

int handle_quotes(const char *input, int *i, int *in_single_quote, int *in_double_quote)
{
	if ((input[*i] == '\'' && !*in_double_quote) || 
		(input[*i] == '\"' && !*in_single_quote))
	{
		*in_single_quote = input[*i] == '\'' ? !*in_single_quote : *in_single_quote;
		*in_double_quote = input[*i] == '\"' ? !*in_double_quote : *in_double_quote;
		(*i)++;
		return 1;
	}
	return 0;
}

int handle_space(const char *input, int *i, int in_single_quote, int in_double_quote)
{
	if (input[*i] == ' ' && !in_single_quote && !in_double_quote)
	{
		while (input[*i] == ' ' && input[*i] != '\0')
			(*i)++;
		return 1;
	}
	return (0);
}

int handle_pipe(const char *input, int *i, int in_single_quote, int in_double_quote)
{
	if (input[*i] == '|' && !in_single_quote && !in_double_quote)
	{
		(*i)++;
		return 1;
	}
	return 0;
}

int count_tokens(const char *input)
{
	int in_single_quote = 0, in_double_quote = 0, tokens = 0, i = 0;
	while (input[i])
	{
		if (handle_space(input, &i, in_single_quote, in_double_quote))
			tokens++;
		else if (!handle_quotes(input, &i, &in_single_quote, &in_double_quote))
		{
			if (handle_pipe(input, &i, in_single_quote, in_double_quote))
				tokens++;
			else
				i++;
		}
	}
	return (in_single_quote || in_double_quote) ? -1 : (tokens + 1);
}

int copy_token(char **tokens, char *start, char *end, int index)
{
	int length = end - start;
	tokens[index] = malloc((length + 1) * sizeof(char));
	if (tokens[index] == NULL)
	{
		while (index > 0)
			free(tokens[--index]);
		return -1;
	}
	strncpy(tokens[index], start, length);
	tokens[index][length] = '\0';
	return 0;
}

int ft_isredirection(char *s) 
{
    return (s[0] == '>' || s[0] == '<');
}

int ft_redirectionlen(char *s) 
{
    if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
        return 2; // For ">>" or "<<"
    return 1; // For single "<" or ">"
}

int ft_tokenlen(char *s) 
{
    unsigned int i = 0;
    while (s[i] && s[i] != ' ' && s[i] != '|' && !ft_isredirection(&s[i]))
        i++;
    return (i);
}

char **ft_strtoken(char *input) 
{
    int token_count = count_tokens(input);
    if (token_count <= 0)
        return NULL;

    char **token = malloc((token_count + 1) * sizeof(char *));
    if (!token)
        return NULL;

    int i = 0, k = 0, in_single_quote = 0, in_double_quote = 0;

    while (input[i]) 
    {
        // Skip leading spaces outside of quotes
        while (input[i] == ' ' && !in_single_quote && !in_double_quote)
            i++;

        // Handle quotes
        if ((input[i] == '\'' || input[i] == '\"') && !(in_single_quote && in_double_quote))
        {
            char quote_type = input[i];
            int start = i;
            in_single_quote = (quote_type == '\'') ? 1 : in_single_quote;
            in_double_quote = (quote_type == '\"') ? 1 : in_double_quote;
            i++;

            while (input[i] && !(input[i] == quote_type && ((quote_type == '\'' && !in_double_quote) || (quote_type == '\"' && !in_single_quote)))) {
                i++;
            }
            if (input[i]) {
                in_single_quote = (quote_type == '\'') ? 0 : in_single_quote;
                in_double_quote = (quote_type == '\"') ? 0 : in_double_quote;
                i++; // Skip the closing quote
            }
            token[k++] = ft_strndup(&input[start], i - start);
            continue;
        }

        // Handle normal tokens, pipes, and operators
        if (!in_single_quote && !in_double_quote) {
            int start = i;
            while (input[i] && input[i] != ' ' && input[i] != '|' && !ft_isredirection(&input[i])) {
                i++;
            }

            if (start != i) {
                token[k++] = ft_strndup(&input[start], i - start);
            }
            if (input[i] == '|') {
                token[k++] = ft_strndup("|", 1);
                i++; // Skip the pipe
            }
        }

        // Handle redirection operators
        if (ft_isredirection(&input[i]) && !in_single_quote && !in_double_quote) {
            int len = ft_redirectionlen(&input[i]);
            token[k++] = ft_strndup(&input[i], len);
            i += len; // Skip over the redirection operator
        } else if (input[i] != '\0') {
	continue;        }
    }
    token[k] = NULL;
    return token;
}
