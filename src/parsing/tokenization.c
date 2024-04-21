/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/20 10:59:16 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isredir(char *s)
{
	if (s == NULL)
	{
		return (0);
	}
	return (ft_strcmp(s, ">") == 0 || ft_strcmp(s, "<") == 0|| ft_strcmp(s, ">>") == 0 || ft_strcmp(s, "<<") == 0);
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

int file_check(t_list *tokens)
{
    while (tokens != NULL) {
        if (ft_isredir(tokens->content) == 1) {
            if (tokens->next == NULL || ft_strcmp(tokens->next->content, "|") == 0) {
                printf("Error: Redirection file incomplete\n");
                return (-1);
            }
        }
        tokens = tokens->next;
    }
    return 0;
}

t_list *ft_strtoken(char *input, t_shell *shell)
{
    int i = 0;
    t_list *token = NULL;
    t_list *last = NULL;
    

    int token_count = count_tokens(input);
    if (token_count < 0)
    {
        free(input);
        printf("Syntax error: Incomplete quote\n");
        return NULL;
    }
    while (input[i])
    {
        t_list *new = extract_token(input, &i, shell);
        if (new == NULL || new->content == NULL)
        {
            continue;
        }
        if (token == NULL)
        {
            token = new;
            last = new;
        } 
        else 
        {
            last->next = new;
            last = new;
            while (last->next)
                last = last->next;
        }
    }
    free(input);
    if (file_check(token) < 0)
    {
        ft_freelst(token);
        return NULL;
    }
    return token;
}
