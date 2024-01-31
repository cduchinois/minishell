/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 11:09:41 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:41:06 by yuewang          ###   ########.fr       */
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
int main(int argc, char *argv[], char *envp[]) 
{
    (void) argc;
    (void) argv;
    char *input;
    char **tokens;
    t_shell *shell;

    //using_history();
    while (1) 
    {
        input = readline("Minishell $> ");
        if (!input) 
            break;
        if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
        //if (*input) 
            //add_history(input);
        tokens = ft_strtoken(input);
        if (tokens) 
        {
            //for (int i = 0; tokens[i] != NULL; i++) 
                //printf("Token %d: %s\n", i, tokens[i]);
            shell = init_struct_shell(tokens, envp);
        }
        ft_execute(shell);
    }
    clear_history();
    //clean_all
    return 0;
}
