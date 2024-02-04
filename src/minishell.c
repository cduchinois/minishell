/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/04 17:28:44 by fgranger         ###   ########.fr       */
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

/*
    Minishell must not have any argument : if argc <> 1
    return and display error
*/
int main(int argc,char **argv,char **envp) 
{
    t_shell *shell;

    if (argc != 1 && argv[1])
        return (EXIT_FAILURE); //Add error msg
    //init_shell(shell);
    //init_signals(shell);
    launch_minishell(shell);    
    //Clean(shell); Free and clean everything
    return (EXIT_SUCCESS);
}
