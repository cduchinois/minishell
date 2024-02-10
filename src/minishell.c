/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 14:49:50 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//signal management to implement in the loop
//loop : read / parse / execute / free

void minishell(t_shell *shell)
{
    char *line;
    
    while (shell->exit == false)
    {
        line = readline("Minishell >");
        if (line && *line)
            add_history(line); // Add non-empty lines to history.
        //mini_parser(shell, line); //only to test before parse line function arrives
        parse_line(shell, line); // initilize prompt scope + process scope
        print_shell(shell);
        //print_prompt(shell->prompt);
        //ft_execute(shell->prompt);
        //clean_prompt(shell->prompt);
        //free(line);
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
    //Clean(shell); Free and clean everything
    return (EXIT_SUCCESS);
}
