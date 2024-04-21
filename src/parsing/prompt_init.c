/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:09:58 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:11:31 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_pipes(t_list *tokens)
{
	int (pipe_count) = 0;
	while (tokens != NULL)
	{
		if (strcmp(tokens->content, "|") == 0)
		{
			pipe_count++;
		}
		tokens = tokens->next;
	}
	return (pipe_count);
}

void	process_division(t_prompt *prompt, t_list *token)
{
	t_list (*current) = token;
	t_list (*start) = token;
	int (process_index) = 0;
	int (token_count) = 0;
	while (current)
	{
		if (strcmp(current->content, "|") == 0 || !current->next)
		{
			if (ft_strcmp(current->content, "|") != 0 && !current->next)
				token_count++;
			prompt->process[process_index] = process_init(start, \
								token_count, process_index, prompt);
			process_index++;
			token_count = 0;
			start = current->next;
		}
		else
			token_count++;
		current = current->next;
	}
}

void	finalize_prompt_setup(t_prompt *prompt)
{
	if (prompt->process_count > 0 && prompt->process[prompt->process_count - 1])
		prompt->last_exit = prompt->process[prompt->process_count - 1] \
		->return_status;
	else
		prompt->last_exit = -1;
	prompt->backup_fd[0] = dup(STDIN_FILENO);
	prompt->backup_fd[1] = dup(STDOUT_FILENO);
}

t_prompt	*prompt_init(t_list *token, t_shell *shell)
{
	t_prompt	*prompt;

	prompt = safe_malloc(sizeof(t_prompt), shell);
	prompt->token = token;
	prompt->process_count = count_pipes(token) + 1;
	prompt->process = safe_malloc(prompt->process_count * \
								sizeof(t_process *), shell);
	prompt->shell = shell;
	process_division(prompt, token);
	finalize_prompt_setup(prompt);
	return (prompt);
}
