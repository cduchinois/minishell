/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:00:39 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/10 21:41:27 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int update_quote_state(char quote, int *in_single_quote, int *in_double_quote)
{
	if (quote == '\'')
	{
		*in_single_quote = !*in_single_quote;
		return *in_double_quote == 0;
	}
	else if (quote == '\"')
	{
		*in_double_quote = !*in_double_quote;
		return *in_single_quote == 0;
	}
	return 0;
}

/*int handle_quotes(const char *input, int *i, int *in_single_quote, int *in_double_quote)
{
	if ((input[*i] == '\'' && !*in_double_quote) || 
		(input[*i] == '\"' && !*in_single_quote))
	{
		*in_single_quote = input[*i] == '\'' ? !*in_single_quote : *in_single_quote;
		*in_double_quote = input[*i] == '\"' ? !*in_double_quote : *in_double_quote;
		(*i)++;
		return 1;
	}
	return 0;
}*/

int handle_space(const char *input, int *i, int in_single_quote, int in_double_quote)
{
	if (input[*i] == ' ' && !in_single_quote && !in_double_quote)
	{
		while (input[*i] == ' ' && input[*i] != '\0')
			(*i)++;
		return 1;
	}
	return (0);
}

int handle_pipe(const char *input, int *i, int in_single_quote, int in_double_quote)
{
	if (input[*i] == '|' && !in_single_quote && !in_double_quote)
	{
		(*i)++;
		return 1;
	}
	return 0;
}

int ft_isredirection(char *s) 
{
    if (s == NULL)
    {
        return 0;
    }
    return (s[0] == '>' || s[0] == '<');
}


int ft_redirectionlen(char *s) 
{
    if ((s[0] == '>' && s[1] == '>') || (s[0] == '<' && s[1] == '<'))
        return 2;
    return 1;
}

int ft_tokenlen(char *s) 
{
    unsigned int i = 0;
    while (s[i] && s[i] != ' ' && s[i] != '|' && !ft_isredirection(&s[i]))
        i++;
    return (i);
}

int find_start(char *input, int *index, bool *in_single_quote, bool *in_double_quote) 
{
    while (input[*index])
    {
        if (!*in_single_quote && !*in_double_quote && input[*index] == ' ')
        {
            (*index)++;
        }
        else if ((input[*index] == '\'' || input[*index] == '\"') && (!*in_single_quote && !*in_double_quote))
        {
            if (input[*index] == '\'')
                *in_single_quote = true;
            else 
                *in_double_quote = true;
            (*index)++;
            return (*index);
        }
        else if (!*in_single_quote && !*in_double_quote && input[*index] == '|')
        {
            return (*index);
        }
        else if (!*in_single_quote && !*in_double_quote && input[*index] == '<' || input[*index] == '>')
        {
            return (*index);
        }
        else 
            return *index;
    }
    return -1;
}

int find_end(char *input, int *index, bool *in_single_quote, bool *in_double_quote)
{
    bool firstIteration = true;
    while (input[*index]) 
    {
        if (!*in_single_quote && !*in_double_quote) {
            if ((input[*index] == '|' || input[*index] == '<' || input[*index] == '>'))
            {
                if (firstIteration) 
                {
                    firstIteration = false;
                    if (input[*index] == '|') {
                        return ++(*index);
                    } else if (input[*index] == '<' || input[*index] == '>') {
                        *index += ft_redirectionlen(input + *index);
                        return *index;
                    }
                }
                else
                    return *index;
            }
        }
        if ((*in_single_quote && input[*index] == '\'') || (*in_double_quote && input[*index] == '\"'))
        {
            *in_single_quote = false;
            *in_double_quote = false;
            (*index)++;
            return (*index - 1);
        } else if (!*in_single_quote && !*in_double_quote && input[*index] == ' ') {
            return *index;
        }

        firstIteration = false;
        (*index)++;
    }
    return *index;
}

char *append_char(char *str, char c)
{
    size_t len = strlen(str);
    char temp[2] = {c, '\0'};
    char *new_str = ft_strjoin(str, temp);
    free(str);
    return new_str;
}


char	*find_var_from_envp(t_lst_env *env, char *var_name)
{
	char	*varible;
	
	while (env)
    {
        if (ft_strncmp(env->key, var_name, ft_strlen(var_name)) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
	return (NULL);
}

char *get_expand_value(char *var_name, t_shell *shell)
{
    char *value;
    
    if (ft_strcmp(var_name, "?") == 0)
    {
        value = ft_itoa(shell->prompt->last_exit);
        return value;
    }
    else 
    {
        value = find_var_from_envp(shell->env, var_name);
        if (value != NULL) 
            return value;
        else 
            return NULL;
    }
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

    while (token[i]) {
        if (token[i] == '\'') {
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

char *extract_token(char *input, int *index, bool *in_single_quote, bool *in_double_quote, t_shell *shell)
{
    bool was_in_single_quote = false;
    int start = find_start(input, index, in_single_quote, in_double_quote);
    if (start == -1)
        return NULL;
    was_in_single_quote = *in_single_quote;
    int end = find_end(input, index, in_single_quote, in_double_quote);
    if (start < end) 
    {
        char *token = ft_strndup(input + start, end - start);
        printf("token: %s\n", token);
        if ((ft_strchr(token, '$') == NULL || was_in_single_quote))
        {
            return token;
        } 
        else 
        {
            char *expanded_token = ft_expand_token(token, shell);
            free(token);
            return expanded_token;
        }
    }
    return NULL;
}

int count_tokens(char *input)
{
    int index = 0;
    int token_count = 0;
    bool in_single_quote = false, in_double_quote = false;

    while (input[index])
    {
        int start = find_start(input, &index, &in_single_quote, &in_double_quote);
        if (start == -1)
            break;

        int end = find_end(input, &index, &in_single_quote, &in_double_quote);
        if (start < end)
        {
            token_count++;
        }
    }
    return token_count;
}

void token_safe_check(char **tokens, bool *in_single_quote, bool *in_double_quote)
{
    int i;

    i = 0;
    if (*in_single_quote || *in_double_quote)
    {
        perror ("Error: incomplete quote\n");
        exit(1);
    }
    while (tokens[i])
    {
        if (ft_isredirection(tokens[i]) == !0)
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
    int i = 0, k = 0;
    bool in_single_quote = false, in_double_quote = false;
    int token_count = count_tokens(input);
    printf("token_count: %d\n", token_count);
    
    if (token_count <= 0) return NULL;

    char **tokens = safe_malloc((token_count + 1) * sizeof(char *), shell);
    if (!tokens) return NULL;
    i = 0;
    
    while (input[i]) 
    {
        char *token = extract_token(input, &i, &in_single_quote, &in_double_quote, shell);
        if (token)
            tokens[k++] = ft_strdup(token);
        free(token);            
    }
    tokens[k] = NULL;
    token_safe_check(tokens, &in_double_quote, &in_single_quote);
    return tokens;
}

/*char *ft_expand_token()(char *token, t_shell *shell)
{
    bool in single quote = false;
    int i = 0;
    char *expanded_token = null;
    in j = 0;
    while (token[i]) {
        if (input[i] == '\'')
            start = end = i++; 
            while (input[end] && input[end] != '\'')
                end++;
            if input[end] == '\''
                check if $ is present from quote start -> end 
                    if yes, dup token's start->end position to expanded_token;
                i+end-start;
            else 
                when meet $ from i position to end of token shoudl process_expansion, then duplicate the expanded string to expanded_token
                break;
        else 
                if meet $ 
                    process_expansion
                else 
                    i++;
}


char **ft_strtoken(char *input, t_shell *shell)
{
    int token_count = count_tokens(input);
    if (token_count <= 0) {
        return NULL;
    }

    char **tokens = safe_malloc((token_count + 1) * sizeof(char *), shell); // Plus one for the NULL terminator
    int i = 0, k = 0;
    bool in_single_quote = false, in_double_quote = false;

    while (input[i]) {
        // Skip leading spaces
        while (input[i] == ' ' && !in_single_quote && !in_double_quote) {
            i++;
        }

        // Start of a new token
        int start = i;

        // Handle quoted strings
        if (input[i] == '\'' || input[i] == '\"') {
            char quote_type = input[i++];
            while (input[i] && input[i] != quote_type) {
                i++;
            }
            if (input[i] == quote_type) {
                i++; // Skip closing quote
            }
            tokens[k++] = ft_strndup(&input[start], i - start);
            continue;
        }

        // Handle normal tokens and operators
        while (input[i] && input[i] != ' ' && input[i] != '|')
        {
            if (ft_isredirection(&input[i])) {
                if (start != i) {
                    // Token before redirection
                    tokens[k++] = ft_strndup(&input[start], i - start);
                }
                int len = ft_redirectionlen(&input[i]);
                tokens[k++] = ft_strndup(&input[i], len);
                i += len; // Skip redirection
                start = i;
            } else {
                i++;
            }
        }

        if (start != i) {
            // End of a normal token
            tokens[k++] = ft_strndup(&input[start], i - start);
        }
        if (input[i] == '|') {
            // Pipe found, add as a separate token
            tokens[k++] = ft_strndup(&input[i++], 1);
        }
    }
    tokens[k] = NULL; // Null-terminate the array
    return tokens;
}*/