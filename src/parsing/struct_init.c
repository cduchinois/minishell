/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:24:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 17:51:10 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_infile *infile_list_init(char **tokens, int token_count, t_process *process, t_shell *shell)
{   
    int i = 0;
    t_lst_infile *head = NULL;
    t_lst_infile *new_node;

    while (i < token_count) {
        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0)) {
            bool is_heredoc = false;
            if (ft_strcmp(tokens[i], "<<") == 0) {
                is_heredoc = true;
            }
            new_node = create_infile_node(tokens[i + 1], is_heredoc, shell);
            if (new_node) {
                append_infile_node(&head, new_node);
            }
            i += 2;
            process->argc -= 2;
        } else {
            i++;
        }
    }
    return head;
}

t_lst_outfile *outfile_list_init(char **tokens, int token_count, t_process *process, t_shell *shell)
{
    t_lst_outfile *head = NULL;
    int i = 0;

    while (i < token_count) {
        if ((ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0) && i + 1 < token_count) {
            int append_mode = O_WRONLY | O_CREAT | O_TRUNC;
            if (ft_strcmp(tokens[i], ">>") == 0) {
                append_mode = O_WRONLY | O_CREAT | O_APPEND;
            }
            t_lst_outfile *new_node = create_outfile_node(tokens[i + 1], append_mode, shell);
            if (new_node) {
                append_outfile_node(&head, new_node);
            }
            i += 2;
            process->argc -= 2;
        } else {
            i++;
        }
    }
    return head;
}


t_process *process_init(char **tokens, int token_count, int index, t_shell *shell, t_prompt *prompt)
{
    
    t_process *process = safe_malloc(sizeof(t_process), shell);
    process->index = index;
    process->argc = token_count;
    process->infile = infile_list_init(tokens, token_count, process, shell);
    process->outfile = outfile_list_init(tokens, token_count, process, shell);
    process->args = extract_arguments(tokens, process->argc, shell);
    if (process->args && process->args[0])
        process->command = ft_strdup(process->args[0]);
    process->fd[0] = -1;
    process->fd[1] = -1;
    process->pid = -1;
    process->return_status = 0;
    process->prompt = prompt;
    process->shell = shell;
    return process;
}

t_prompt *prompt_init(char *line, char **tokens, t_shell *shell)
{
    t_prompt *prompt;

    prompt = safe_malloc(sizeof(t_prompt), shell);
    prompt->user_input = line;
    prompt->tokens = tokens;
    prompt->process_count = count_pipes(tokens) + 1;
    prompt->process = safe_malloc(prompt->process_count * sizeof(t_process *), shell);
    int start = 0;
    int i = 0;
    while (i < prompt->process_count) 
    {
        int end = start;
        while (tokens[end] && strcmp(tokens[end], "|") != 0)
            end++;
        prompt->process[i] = process_init(&tokens[start], end - start, i, shell, prompt);
        if (!prompt->process[i]) 
        {
            clean(shell);
            exit(EXIT_FAILURE);
        }
        start = end + 1;
        i++;
    }
    prompt->last_exit = prompt->process[prompt->process_count - 1]->return_status;
    prompt->shell = shell;
    return (prompt);
}