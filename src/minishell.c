/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 13:32:34 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//signal management to implement in the loop
//loop : read / parse / execute / free

void minishell(t_shell *shell)
{
	char *line;
	
	setup_signal_handlers();
	while (!shell->exit) 
	{
		line = readline("Minishell >");
		if (!line) 
		{
			if (rl_end == 0)
				shell->exit = true;
			else
				continue;
		}
		else 
		{
			setup_signal_handlers_non_empty_line();
			add_history(line);
			parse_line(shell, line);
            // print_prompt(shell->prompt);
			if (shell->prompt)
			{ 	
				ft_execute(shell->prompt);
				free_prompt(shell->prompt);
			}
			setup_signal_handlers();
		}
	}
}

/*
	Minishell must not have any argument : if argc <> 1 return and display error
	init all shell informations including signal init
	launch the minishell loop
	Clean everything
	return succes
*/

int main(int argc, char **argv, char **envp) 
{
	t_shell *shell = NULL;
	
	(void)**argv;
	if (argc != 1)
		return (EXIT_FAILURE); //Add error msg
	init_shell(&shell, envp);
	minishell(shell);
	clean(shell);
	//free process
	return (EXIT_SUCCESS);
}
