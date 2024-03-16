/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 11:28:52 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isredir(char *s)
{
	if (s == NULL)
	{
		return (0);
	}
	return (s[0] == '>' || s[0] == '<');
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
	{
		perror ("Error: incomplete quote\n");
		exit(1);
	}
	return (token_count);
}

void redir_delim_check(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_isredir(tokens[i]) == !0)
		{
			if (!tokens[i + 1] || ft_strcmp(tokens[i + 1], "|") == 0)
			{
				perror ("Error: redirection file missing\n");
				exit(1);
			}
		}    
		i++;
	}
}

char **ft_strtoken(char *input, t_shell *shell)
{
	char	**tokens;
	int		i;
	int		k;

	i = 0;
	k = 0;
	int token_count = count_tokens(input);
	if (token_count <= 0)
		return (NULL);
	tokens = safe_malloc((token_count + 1) * sizeof(char *), shell);
	while (input[i]) 
	{
		tokens[k] = extract_token(input, &i, shell);
		if (tokens[k])
			k++;
	}
	tokens[k] = NULL;
	redir_delim_check(tokens);
	return (tokens);
}
