/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:19:32 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/17 19:48:26 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_expand_value(char *var_name, t_shell *shell)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
	{
		value = ft_itoa(shell->exit_status);
		return (value);
	}
	else
	{
		value = find_var_from_envp(shell->env, var_name);
		if (value)
			return (value);
		else
			return (NULL);
	}
}

char	*append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	len = ft_strlen(str);
	new_str = ft_strjoin(str, temp);
	free(str);
	return (new_str);
}

char	*expand_variable(char *str, const char *token, int *i, t_shell *shell)
{
	char	*var_name;
	char	*value;
	char	*new_str;

	int (start) = *i + 1;
	while (token[*i + 1] != ' ' && token[*i + 1] != '\t')
		(*i)++;
	if (*i == start)
		return (str);
	var_name = ft_strndup(token + start, *i - start + 1);
	value = get_expand_value(var_name, shell);
	if (value)
	{
		new_str = ft_strjoin(str, value);
		free(str);
		str = new_str;
	}
	free(var_name);
	return (str);
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

char	*ft_expand_token(char *token, t_shell *shell)
{
	char	*expanded_token;
	int		i;

	i = 0;
	expanded_token = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '\'')
			expanded_token = handle_quotes(expanded_token, token, &i);
		else if (token[i] == '$' && token[i + 1] != ' ' \
				&& token[i + 1] != '\t' && token[i + 1] != '\0')
			expanded_token = expand_variable(expanded_token, token, &i, shell);
		else
		{
			expanded_token = append_char(expanded_token, token[i]);
			i++;
		}
	}
	return (expanded_token);
}	
