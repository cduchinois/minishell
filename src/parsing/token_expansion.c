/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:19:32 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 12:09:00 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//expand token
char *get_expand_value(char *var_name, t_shell *shell)
{
    char *value;
    
    if (ft_strcmp(var_name, "?") == 0)
    {
        value = ft_itoa(shell->exit_status);
        return value;
    }
    else 
    {
        value = find_var_from_envp(shell->env, var_name);
        if (value) 
            return value;
        else 
            return NULL;
    }
}

char *append_char(char *str, char c)
{
    size_t len = ft_strlen(str);
    char temp[2] = {c, '\0'};
    char *new_str = ft_strjoin(str, temp);
    free(str);
    return new_str;
}

char *expand_variable(char *str, const char *token, int *i, t_shell *shell)
{
    int start = ++(*i);
    while (token[*i])
        (*i)++;
    char *var_name = ft_strndup(token + start, *i - start);
    char *value = get_expand_value(var_name, shell);
    if (value)
    {
        char *new_str = ft_strjoin(str, value);
        free(str);
        str = new_str;
    }
    free(var_name);
    (*i)--;
    return str;
}

char *handle_quotes(char *str, const char *token, int *i)
{
    int start = (*i)++;
    while (token[*i] && token[*i] != '\'')
        (*i)++;
    int len = *i - start + 1;
    char *temp = ft_strndup(token + start, len + 1);
    char *new_str = ft_strjoin(str, temp);
    free(str);
    free(temp);
    (*i)++;
    return new_str;
}

char *ft_expand_token(char *token, t_shell *shell)
{
    char *expanded_token = ft_strdup("");
    int i = 0;

    while (token[i])
    {
        if (token[i] == '\'')
        {
            expanded_token = handle_quotes(expanded_token, token, &i);
        }
        else if (token[i] == '$')
        {
            expanded_token = expand_variable(expanded_token, token, &i, shell);
        } 
        else
        {
            expanded_token = append_char(expanded_token, token[i]);
        }
        i++;
    }
    return expanded_token;
}
