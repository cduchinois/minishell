/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:24:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 20:11:25 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_arguments(t_list *token, t_shell *shell)
{
	int (count) = 0;
	t_list (*current) = token;
	while (current)
	{
		if (ft_isredir((char *)current->content))
		{
			if (current->next)
				current = current->next;
			else
			{
				ft_putstr_fd("Redirection missing filename, \
								please specify: ", 2);
				exit(2);
			}
		}
		else
			count++;
		current = current->next;
	}
	return (count);
}

bool	assign_argument(char **args, int *i, char *content)
{
	args[*i] = ft_strdup(content);
	if (args[*i] == NULL)
	{
		while ((*i)-- > 0)
			free(args[*i]);
		return (false);
	}
	(*i)++;
	return (true);
}

char	**extract_arguments(t_list *start, int argc, t_shell *shell)
{
	char	**args;

	int (i) = 0;
	t_list (*current) = start;
	args = safe_malloc((argc + 1) * sizeof(char *), shell);
	while (current && i < argc)
	{
		if (strcmp(current->content, "|") == 0)
			break ;
		if (ft_isredir((char *)current->content) && current->next)
				current = current->next;
		else
		{
			if (!assign_argument(args, &i, (char *)current->content))
			{
				free(args);
				return (NULL);
			}
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

t_process	*process_init(t_list *start, int token_count, \
						int index, t_prompt *prompt)
{
	t_process	*process;

	process = safe_malloc(sizeof(t_process), prompt->shell);
	ft_memset(process, 0, sizeof(t_process));
	process->index = index;
	process->argc = token_count;
	process->file = file_list_init(start, process, prompt->shell);
	process->args = extract_arguments(start, token_count, prompt->shell);
	if (process->args && process->args[0])
		process->command = ft_strdup(process->args[0]);
	process->fd[0] = -1;
	process->fd[1] = -1;
	process->pid = -1;
	process->return_status = 0;
	process->prompt = prompt;
	process->shell = prompt->shell;
	return (process);
}
