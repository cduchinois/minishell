/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:06:52 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	file_check(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (ft_isredir(tokens->content) == 1)
		{
			if (tokens->next == NULL || \
			ft_strcmp(tokens->next->content, "|") == 0)
			{
				printf("Error: Redirection file incomplete\n");
				return (-1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

bool	check_token_count(char **input)
{
	int	token_count;

	token_count = count_tokens(*input);
	if (token_count < 0)
	{
		free(*input);
		printf("Syntax error: Incomplete quote\n");
		return (false);
	}
	return (true);
}

void	manage_token_chain(t_list **token, t_list **last, t_list *new)
{
	if (*token == NULL)
	{
		*token = new;
		*last = new;
	}
	else
	{
		(*last)->next = new;
		*last = new;
	}
	while ((*last)->next)
		*last = (*last)->next;
}

t_list	*finalize_token_list(char *input, t_list *token)
{
	free(input);
	if (file_check(token) < 0)
	{
		ft_freelst(token);
		return (NULL);
	}
	return (token);
}

t_list	*ft_strtoken(char *input, t_shell *shell)
{
	t_list	*new;

	int (i) = 0;
	t_list (*token) = NULL;
	t_list (*last) = NULL;
	if (!check_token_count(&input))
		return (NULL);
	while (input[i])
	{
		new = extract_token(input, &i, shell);
		if (new == NULL || new->content == NULL)
			continue ;
		manage_token_chain(&token, &last, new);
	}
	return (finalize_token_list(input, token));
}
