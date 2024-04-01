/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:36:13 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 13:54:17 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



char	**extract_arguments(char **tokens, int argc, t_shell *shell)
{
	char	**args;

	int (i) = 0;
	int (j) = 0;
	args = safe_malloc((argc + 1) * sizeof(char *), shell);
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
	return (args);
}

void	parse_line(t_shell *shell, char *line)
{
	char	*input;
	t_list	*token;

	input = ft_strdup(line);
	token = ft_strtoken(input, shell);
    // while (token)
    // {
    //     printf("token:%s\n", token->content);
    //     token = token->next;
    // }
	if (!token)
	{
		free(input);
		return ;
	}
	shell->prompt = prompt_init(line, token, shell);
}