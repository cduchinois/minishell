/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:01:32 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 15:01:17 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char s)
{
	if (!s)
		return (0);
	return (s == '\'' || s == '"');
}

char	*handle_quotes(char *str, const char *token, int *i)
{
	int		len;
	char	*new_str;
	char	*temp;

	int (start) = (*i)++;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	len = *i - start + 1;
	temp = ft_strndup(token + start, len + 1);
	new_str = ft_strjoin(str, temp);
	free(str);
	free(temp);
	(*i)++;
	return (new_str);
}

char *remove_quotes(char *token, char quote)
{
    char *result = malloc(ft_strlen(token) + 1);
    if (!result) 
        return NULL;
    while (token)
    {
        if (*token != quote)
            *result++ = *token;
        token++;
    }
    *result = '\0';
    free(token);
    return (result);
}

char *trim_quote(char *token)
{
    char    *str = token;
    size_t  len = strlen(str);
    int     single_quotes = 0;
    int     double_quotes = 0;
    size_t i = 0;
    
    while (i < len)
    {
        if (str[i] == '\'')
            single_quotes++;
        else if (str[i] == '"')
            double_quotes++;
        i++;
    }
    if (single_quotes && single_quotes % 2 == 0)
        token = remove_quotes(token, '\'');
    if (double_quotes && double_quotes % 2 == 0)
        token = remove_quotes(token, '"');
    return (token);
}