/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:39:08 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/13 19:46:21 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_infile_list(t_lst_infile *head) 
{
    t_lst_infile *tmp;
    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp->name);
        if (tmp->here_doc)
            unlink(".here_doc");
        free(tmp);
    }
}

void free_outfile_list(t_lst_outfile *head)
{
    t_lst_outfile *tmp;
    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
}

void free_process(t_process *process)
{
    if (process)
    {
        if(process->command)
            free(process->command);
        if(process->pathname)
            free(process->pathname);
        if(process->args)
            ft_freetab(process->args);
        if(process->infile)
            free_infile_list(process->infile);
        if(process->outfile)
            free_outfile_list(process->outfile);
        free(process);
    }
}

void free_prompt(t_prompt *prompt) 
{
    if (prompt)
    {
        if (prompt->user_input)
            free(prompt->user_input);
        if (prompt->token)
            ft_freelst(prompt->token);
        int i = 0;
        while (i < prompt->process_count)
        {
            if (prompt->process[i])
                free_process(prompt->process[i]);
            i++;
        }   
        free(prompt->process);
    }
}

void ft_free_env(t_lst_env *env)
{
    t_lst_env *temp;

    while (env)
    {
        temp = env;
        env = env->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

void cleanup_readline()
{
    clear_history();  // Clear the history list by removing all items
    rl_clear_history();  // Frees the history list; requires newer versions of readline
    rl_cleanup_after_signal();  // Clean up Readline state after a signal
    rl_deprep_terminal();  // De-initialize the terminal for Readline
}

void clean(t_shell *shell) 
{
    if (shell)
    {
        if (shell->env)
            ft_free_env(shell->env);
        if (shell->prompt)
            free_prompt(shell->prompt);
        cleanup_readline();
        free(shell);
    }
}