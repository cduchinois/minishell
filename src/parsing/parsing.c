/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:36:13 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 12:10:43 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int count_pipes(char **tokens) 
{
    int pipe_count = 0;
    int i = 0;

    while (tokens[i]) 
    {
        if (strcmp(tokens[i], "|") == 0) {
            pipe_count++;
        }
        i++;
    }
    return pipe_count;
}

char **extract_arguments(char **tokens, int argc, t_shell *shell)
{
    char **args = safe_malloc((argc + 1) * sizeof(char *), shell);
    int i = 0, j = 0;
    while (j < argc)
    {
        if (ft_isredir(tokens[i]) && tokens[i + 1])
        {
            i += 2;
        }
        else if (ft_isredir(tokens[i]) && !tokens[i + 1])
        {
            i ++;
        }
        else
        {
            args[j] = ft_strdup(tokens[i]);
            j++;
            i++;
        }
    }
    args[j] = NULL;
    return args;
}

void parse_line(t_shell *shell, char *line) 
{
    char *input = ft_strdup(line);
    char **tokens = ft_strtoken(input, shell);
    if (!tokens) return;
    shell->prompt = prompt_init(line, tokens, shell);
}