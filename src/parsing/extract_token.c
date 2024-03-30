/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/30 17:47:15 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isquote(char s)
{
	if (!s)
		return (0);
	return (s == '\'' || s == '\"');
}

// Assuming ft_isquote is a function that checks if a character is a quote (' or ")
// You might need to define it or use your existing logic


int find_start(char *input, int *index, bool *in_squote, bool *in_dquote) {
    while (input[*index]) {
        if (!*in_squote && !*in_dquote && (input[*index] == ' ' || input[*index] == '\t')) {
            (*index)++;
        }
        else if (!*in_squote && !*in_dquote && ft_isquote(input[*index]) == 1) {
            // If a quote is found, set the appropriate flag
            if (input[*index] == '\'') {
                *in_squote = true;
            } else if (input[*index] == '"') {
                *in_dquote = true;
            }
            // Increment the index to skip over the quote itself
            (*index)++;
            break; // Break after skipping the quote to handle the inside of the quote properly
        }
        else {
            break; // Found a non-whitespace, non-quote character or are inside quotes
        }
    }

    // If reached the end of the string without finding a start, return -1
    if (input[*index] == '\0') {
        return -1;
    }
    return *index; // Return the updated index marking the start of a segment
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

void remove_quotes(char **token, char quote) {
    char *result = malloc(strlen(*token) + 1); // Allocate enough memory for the new string
    if (!result) return; // Check for allocation failure

    char *src = *token;
    char *dst = result;
    while (*src) {
        if (*src != quote) { // Copy over characters that aren't the target quote
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // Null-terminate the new string

    free(*token); // Free the original string
    *token = result; // Update the token pointer to the new string
}

void trim_quote(char **token) {
    char *str = *token;
    size_t len = strlen(str);
    int single_quotes = 0, double_quotes = 0;

    // Count occurrences of each quote type
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == '\'') single_quotes++;
        else if (str[i] == '"') double_quotes++;
    }

    // If an even number of quotes is found, remove them
    if (single_quotes % 2 == 0) {
        remove_quotes(token, '\'');
    }
    if (double_quotes % 2 == 0) {
        remove_quotes(token, '"');
    }
}

char	*extract_token(char *input, int *index, t_shell *shell)
{
	bool	was_in_single_quote;
    bool    was_in_double_quote;
	char	*token;

	bool (squote) = false;
	bool (dquote) = false;
	int (start) = find_start(input, index, &squote, &dquote);
	if (start == -1)
		return (NULL);
        // printf("start_index:%d\n", *index);
	    was_in_single_quote = squote;
    	was_in_double_quote = dquote;

	int (end) = find_end(input, index, &squote, &dquote);
            // printf("end_index:%d\n", *index);

	if (start < end)
	{
		token = ft_strndup(input + start, end - start);
		if (!(was_in_double_quote || was_in_single_quote))
            trim_quote(&token);         
		if(ft_strchr(token, '$') && !was_in_single_quote)
			token = ft_expand_token(token, shell);
	    return (token);
	}
    else 
        return NULL;
}
