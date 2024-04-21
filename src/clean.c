/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:39:08 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 02:43:21 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_file_list(t_lst_file *head) 
{
    t_lst_file *tmp;
    while (head) 
    {
        tmp = head;
        head = head->next;
        free(tmp->name);
        if (tmp->type == 0 && tmp->mode == 1)
            unlink(".here_doc");
        free(tmp);
    }
}

// typedef	struct s_process
// {
// 	int		index;
// 	char	*command;
// 	char	*pathname;
// 	int		argc;
// 	char	**args;
// 	int		*delimiters;
// 	int		fd[2];
// 	int		pid;
// 	int return_status;
// 	t_lst_file *file;
// 	t_prompt *prompt;
// 	t_shell *shell;
// } t_process;

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
        if(process->file)
            free_file_list(process->file);
        free(process);
    }
}

void cleanup_resources(t_prompt *prompt)
{
    // Free process structures
    for (int i = 0; i < prompt->process_count; i++) {
        if (prompt->process[i]) {
            ft_freetab(prompt->process[i]->args); // Free arguments array
            free(prompt->process[i]->command);    // Free command string
            free(prompt->process[i]);             // Free the process structure itself
        }
    }
    free(prompt->process); // Free the array of processes

    // Close open file descriptors if they are not standard input/output/error
    if (prompt->backup_fd[0] != 0) close(prompt->backup_fd[0]);
    if (prompt->backup_fd[1] != 1) close(prompt->backup_fd[1]);

    // Clear other dynamically allocated resources
    ft_free_env(prompt->shell->env); // Assuming you have a function to clear the environment list
}
void free_prompt(t_prompt *prompt) 
{
    if (!prompt)
            return ;
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
    free(prompt);
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
        cleanup_readline();
        free(shell);
    }
}

