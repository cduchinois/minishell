/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:07:02 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:07:39 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isredir(char *s)
{
	if (s == NULL)
	{
		return (0);
	}
	return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<") == 0 || \
			ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
}

int	ft_redirlen(char *s)
{
	if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
		return (2);
	return (1);
}

int	count_tokens(char *input)
{
	int		start;
	int		end;

	bool (squote) = false;
	bool (dquote) = false;
	int (i) = 0;
	int (token_count) = 0;
	while (input[i])
	{
		start = find_start(input, &i, &squote, &dquote);
		if (start == -1)
			break ;
		end = find_end(input, &i, &squote, &dquote);
		if (start < end)
			token_count++;
	}
	if (squote || dquote)
		return (-1);
	return (token_count);
}
