/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 15:11:19 by yuewang          ###   ########.fr       */
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

/*int copy_token(char **tokens, char *start, char *end, int index)
{
	int length = end - start;
	tokens[index] = safe_malloc((length + 1) * sizeof(char), shell);
	if (tokens[index] == NULL)
	{
		while (index > 0)
			free(tokens[--index]);
		return -1;
	}
	strncpy(tokens[index], start, length);
	tokens[index][length] = '\0';
	return 0;
}*/

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

char **ft_strtoken(char *input, t_shell *shell)
{
    int token_count = count_tokens(input);
    if (token_count <= 0) {
        return NULL;
    }

    char **tokens = safe_malloc((token_count + 1) * sizeof(char *), shell); // Plus one for the NULL terminator
    int i = 0, k = 0;
    bool in_single_quote = false, in_double_quote = false;

    while (input[i]) {
        // Skip leading spaces
        while (input[i] == ' ' && !in_single_quote && !in_double_quote) {
            i++;
        }

        // Start of a new token
        int start = i;

        // Handle quoted strings
        if (input[i] == '\'' || input[i] == '\"') {
            char quote_type = input[i++];
            while (input[i] && input[i] != quote_type) {
                i++;
            }
            if (input[i] == quote_type) {
                i++; // Skip closing quote
            }
            tokens[k++] = ft_strndup(&input[start], i - start);
            continue;
        }

        // Handle normal tokens and operators
        while (input[i] && input[i] != ' ' && input[i] != '|')
        {
            if (ft_isredirection(&input[i])) {
                if (start != i) {
                    // Token before redirection
                    tokens[k++] = ft_strndup(&input[start], i - start);
                }
                int len = ft_redirectionlen(&input[i]);
                tokens[k++] = ft_strndup(&input[i], len);
                i += len; // Skip redirection
                start = i;
            } else {
                i++;
            }
        }

        if (start != i) {
            // End of a normal token
            tokens[k++] = ft_strndup(&input[start], i - start);
        }
        if (input[i] == '|') {
            // Pipe found, add as a separate token
            tokens[k++] = ft_strndup(&input[i++], 1);
        }
    }

    tokens[k] = NULL; // Null-terminate the array
    return tokens;
}