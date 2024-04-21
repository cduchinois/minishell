/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 18:01:32 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 15:36:33 by yuewang          ###   ########.fr       */
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

char *trim_quote(char *str) {
    size_t len = strlen(str);
    if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))) {
        str[len - 1] = '\0';
        return str + 1;
    }
    return str;
}

// Function to remove quotes from a string
char *remove_quotes(char *str, char quote) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    while (start <= end && *start == quote) {
        start++;
    }
    while (end >= start && *end == quote) {
        *end = '\0';
        end--;
    }
    return start;
}
