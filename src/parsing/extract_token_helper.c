/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:05:56 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_start(char *input, int *index, bool *in_squote, bool *in_dquote)
{
	while (input[*index])
	{
		if (!*in_squote && !*in_dquote && (input[*index] == ' ' \
			|| input[*index] == '\t'))
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

int	ft_incrementer(char *input, int *index)
{
	if (input[*index] == '|')
		(*index)++;
	else
		*index += ft_redirlen(input + *index);
	return (*index);
}

void	handle_unquoted(char *input, int *index, bool *squote, bool *dquote)
{
	while (input[*index] && !*squote && !*dquote)
	{
		if (input[*index] == ' ')
			break ;
		else if (input[*index] == '|' || input[*index] == '<' \
		|| input[*index] == '>')
			break ;
		else if (input[*index] == '\'')
			*squote = true;
		else if (input[*index] == '"')
			*dquote = true;
		(*index)++;
	}
}

void	handle_quotes2(char *input, int *index, bool *squote, bool *dquote)
{
	while (input[*index])
	{
		if ((*squote && input[*index] == '\'') \
			|| (*dquote && input[*index] == '"'))
		{
			*squote = false;
			*dquote = false;
			(*index)++;
			if (!input[*index] || input[*index] == ' ' || input[*index] == '\t')
				break ;
		}
		else
		{
			(*index)++;
			if (!input[*index])
				break ;
		}
	}
}

int	find_end(char *input, int *index, bool *squote, bool *dquote)
{
	if (!(*squote || *dquote) && (input[*index] == '|' \
		|| input[*index] == '<' || input[*index] == '>'))
		return (ft_incrementer(input, index));
	handle_unquoted(input, index, squote, dquote);
	if (*squote || *dquote)
		handle_quotes2(input, index, squote, dquote);
	return (*index);
}
