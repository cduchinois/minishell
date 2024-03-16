/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:19:07 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 17:32:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// CTRL-C = SIGINT.
// CTRL-\ = SIGQUIT.
void handle_sigint(int sig) {
    // For Ctrl-C, simply print a new line and prompt in main loop; do minimal here.
    (void)sig; // Prevent unused variable warning.
    write(STDOUT_FILENO, "\n", 1); // Move to a new line.
    rl_on_new_line();
    rl_replace_line("", 0); // Clear the line.
    rl_redisplay(); // Redisplay the prompt on a new line.
}

void handle_sigint_interactive(int sig) {
    // For Ctrl-C, simply print a new line and prompt in main loop; do minimal here.
    (void)sig; // Prevent unused variable warning.
    write(STDOUT_FILENO, "\n", 1); // Move to a new line.
    rl_on_new_line();
    rl_replace_line("", 0); // Clear the line.
    // rl_redisplay(); // Redisplay the prompt on a new line.
}


void handle_sigquit(int sig) {
    (void)sig;
    printf("\nQuit\n");
    exit(EXIT_SUCCESS); 
}

// Handles setup for when the input line is empty
void setup_signal_handlers()
{
    struct sigaction sa_int, sa_quit;

    // Setup for SIGINT remains the same
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    // Ignore SIGQUIT
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

// Handles setup for when the input line is not empty
void setup_signal_handlers_non_empty_line()
{
    struct sigaction sa_int, sa_quit;

    // Setup for SIGINT remains the same
    sa_int.sa_handler = handle_sigint_interactive;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    // Exit on SIGQUIT
     sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0; // No special flags
    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
        perror("Error setting SIGQUIT handler");
    }
}


