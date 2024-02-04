/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/04 21:28:44 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*void print_history()
{
    HIST_ENTRY **the_history_list = history_list();
    if (the_history_list)
    {
        for (int i = 0; the_history_list[i]; i++)
        {
            printf("%d: %s\n", i + 1, the_history_list[i]->line);
        }
    }
}*/

//signal management to implement in the loop
//loop : read / parse / execute / free

static void minishell(t_shell *shell)
{
    char *line;
    
    while (shell->exit == false)
    {
        line = readline("minishell >");
        mini_parser(shell, line); //only to test before parse line function arrives
        //parse_line(shell, line); // initilize prompt scope + process scope
        //print_prompt(shell->prompt);
        ft_execute(shell->prompt);
        //clean_prompt(shell->prompt);
    }
}

// initializing all variable of the minishell scope
//envp is a constant to be able to modify it if required during the execution it is duplicated into not const char *
static void init_shell(t_shell *shell, char **envp)
{
    int i;

    i = 0;
    while (envp[i])
        i++;
    shell->env = safe_malloc(sizeof(char *) * i, shell);
    i = 0;
    while (envp[i])
    {
        shell->env[i] = ft_strdup(envp[i]); //to recode to safe the dup malloc
        i++;
    }
    shell->prompt = NULL;
    shell->exit = false;
    shell->exit_status = 0;
    shell->pid = 0;
    shell->sigquit = 0;
    shell->sigint = 0;
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
    t_shell *shell;

    if (argc != 1)
        return (EXIT_FAILURE); //Add error msg
    shell = safe_malloc(sizeof(t_shell), shell);
    init_shell(shell, envp);
    //print_shell(shell);
    minishell(shell);    
    //Clean(shell); Free and clean everything
    return (EXIT_SUCCESS);
}
