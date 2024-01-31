/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initiation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:36:13 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:38:36 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int count_pipes(char **tokens) 
{
    int pipe_count = 0;

    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(tokens[i], "|") == 0) {
            pipe_count++;
        }
    }
    return pipe_count;
}

char *get_infile(char **tokens, int *token_count, int *here_doc)
{
    for (int i = 0; i < *token_count - 1; i++)
    {
        if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], "<<") == 0) 
        {
            *here_doc = strcmp(tokens[i], "<<");
            char *infile = strdup(tokens[i + 1]);
            *token_count -= 2;
            return infile;
        }
    }
    return NULL;
}

char *get_outfile(char **tokens, int *token_count, int *append_mode)
{
    for (int i = 0; i < *token_count - 1; i++)
    {
        if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0) {
            *append_mode = (strcmp(tokens[i], ">>"));
            char *outfile = strdup(tokens[i + 1]);
            // Remove the redirection and filename tokens
            *token_count -= 2;
            return outfile;
        }
    }
    return NULL;
}

char **extract_arguments(char **tokens, int token_count) 
{
    char **args = malloc(sizeof(char *) * (token_count + 1));
    if (!args) return NULL;

    int j = 0;
    for (int i = 0; i < token_count; i++)
    {
        if (!ft_isredirection(tokens[i]) && (i == 0 || !ft_isredirection(tokens[i - 1])))
            args[j++] = strdup(tokens[i]);
    }
    args[j] = NULL;
    return args;
}


t_process *init_struct_process(char **tokens, int token_count, int index, char **env)
{
    t_process *process = malloc(sizeof(t_process));
    if (!process) return NULL;

    process->index = index;
    process->here_doc = 0;
    process->append_mode = 0;
    process->infile = get_infile(tokens, &token_count, &process->here_doc); //Implement a function parse the tokens and check if input redirection sign is present in the tokens, if yes and if it's < infile, return infile and here_doc = 0, if it's a << aka heredoc mode, return heredoc deliminator string as infile and process->here_doc = 1, otherwise return null for infile
    process->outfile = get_infile(tokens, &token_count, &process->append_mode); //Implement a function parse the tokens and check if output redirection sign is present in the tokens, if yes and if it's > outfile, return outfile and appendmode = 0, if it's a >> aka append mode, return outfile and process->append_mode = 1, otherwise return null for outfile
    process->args = extract_arguments(tokens, token_count); // parse tokens, exclude redirection tokens and the file token after them and all null at the end
    process->command = process->args[0]; 
    process->pathname = get_pathname(env, process->command);
    return process;
}

t_shell *init_struct_shell(char **tokens, char *envp[])//HIST_ENTRY **history_list, 
{
    t_shell *shell = malloc(sizeof(t_shell));
    if (!shell) return NULL;
    shell->process_count = count_pipes(tokens) + 1;
    //shell->history = history_list;
    shell->env = envp;
    shell->processes = malloc(sizeof(t_process *) * shell->process_count);
    int start = 0;
    for (int i = 0; i < shell->process_count; i++) 
    {
        int end = start;
        while (tokens[end] && strcmp(tokens[end], "|") != 0) {
            end++;
        }
        shell->processes[i] = init_struct_process(&tokens[start], end - start, i, envp);
        start = end + 1;
    }
    for (int i = 0; i < shell->process_count; i++) 
    {
        ft_fd_in(i, shell->processes); //setup shell->processes[i]->fd[0]
        ft_fd_out(i, shell->processes, shell->process_count); //setup shell->processes[i]->fd[1]
    }
    if (shell->process_count > 1)
    {
        shell->pid = (int *)malloc(sizeof(int) * (shell->process_count));
	    //if (!shell->pid)
		//    error_handle;
    }
    else 
    {
        shell->pid = NULL;
    }
    return shell;
}


