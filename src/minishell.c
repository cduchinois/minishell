/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 17:49:47 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//signal management to implement in the loop
//loop : read / parse / execute / free

int ft_parsing_error(int error_code)
{
    if error_code == EMPTY
        return (EXIT_FAILURE);
    else if error_code == QUOTES
    {
        ft_printf("quote error");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}


void minishell(t_shell *shell) {
    char *line;

    // Initialize with the default signal handlers
    setup_signal_handlers();

    while (!shell->exit) {
        line = readline("Minishell >");
        
        if (!line) {
            if (rl_end == 0) { // Ctrl-D (EOF) on an empty prompt.
                shell->exit = true;
            } else {
                continue; // Ignore Ctrl-D with input, effectively getting a new prompt.
            }
        } else {
            // if (line && *line) {
                setup_signal_handlers_non_empty_line();
                add_history(line); // Add non-empty lines to history.
                parse_line(shell, line);

                if (ft_parsing_error(shell->error))// Initialize prompt scope + process scope
                    ft_execute(shell->prompt); // Execute the parsed command
            // } else {
            //     // If line is effectively empty (only spaces, for instance), revert to default handling
                setup_signal_handlers();
            free(line); // Free the line
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
    //Clean(shell); Free and clean everything
    return (EXIT_SUCCESS);
}
