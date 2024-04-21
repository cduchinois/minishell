/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:20:29 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:08:36 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*create_token(t_shell *shell, char *token_str)
{
	t_list	*token;

	if (token_str[0] == '\0')
	{
		free(token_str);
		return (NULL);
	}
	token = safe_malloc(sizeof(t_list), shell);
	ft_memset(token, 0, sizeof(t_list));
	token->content = token_str;
	return (token);
}

void	process_quotes(char **token_str, bool was_in_double_quote, \
		bool was_in_single_quote)
{
	if (!(was_in_double_quote || was_in_single_quote))
		trim_quote(token_str);
	if (was_in_double_quote)
		remove_quotes(token_str, '"');
	if (was_in_single_quote)
		remove_quotes(token_str, '\'');
}

t_list	*extract_token(char *input, int *index, t_shell *shell)
{
	char	(*token_str);

	bool (was_in_single_quote) = false;
	bool (was_in_double_quote) = false;
	bool (in_squote) = false;
	bool (in_dquote) = false;
	int (start) = find_start(input, index, &in_squote, &in_dquote);
	if (start == -1)
		return (NULL);
	was_in_single_quote = in_squote;
	was_in_double_quote = in_dquote;
	int (end) = find_end(input, index, &in_squote, &in_dquote);
	if (start < end || was_in_double_quote || was_in_single_quote)
	{
		token_str = ft_strndup(input + start, end - start);
		process_quotes(&token_str, was_in_double_quote, was_in_single_quote);
		token_str = handle_expansions(token_str, shell, was_in_single_quote, \
										was_in_double_quote);
		if (token_str == NULL)
			return (NULL);
		return (create_token(shell, token_str));
	}
	return (NULL);
}
