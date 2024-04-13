/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:24:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/13 19:29:53 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_infile *infile_list_init(t_list *tokens, t_process *process, t_shell *shell) {
    t_lst_infile *head = NULL;
    bool is_heredoc = false;
    t_list *current = tokens;

    while (current && current->next) { // Ensure there's a token and a next token
        if (strcmp(current->content, "<") == 0 || strcmp(current->content, "<<") == 0) {
            is_heredoc = strcmp(current->content, "<<") == 0;
            t_lst_infile *new_node = create_infile_node(current->next->content, is_heredoc, shell);
            if (new_node) {
                append_infile_node(&head, new_node);
            }
            current = current->next->next; // Move past the redirection token and its file
            process->argc -= 2; // Adjust argument count for each redirection found
        } else {
            current = current->next; // Move to the next token if not a redirection
        }
    }
    return head;
}

t_lst_outfile *outfile_list_init(t_list *tokens, t_process *process, t_shell *shell) {
    t_lst_outfile *head = NULL;
    int append_mode = O_WRONLY | O_CREAT | O_TRUNC; // Default to overwrite
    t_list *current = tokens;

    while (current && current->next) { // Ensure there's a token and a next token
        if (strcmp(current->content, ">") == 0 || strcmp(current->content, ">>") == 0) {
            append_mode = strcmp(current->content, ">>") == 0 ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC;
            t_lst_outfile *new_node = create_outfile_node(current->next->content, append_mode, shell);
            if (new_node) {
                append_outfile_node(&head, new_node);
            }
            current = current->next->next; // Move past the redirection token and its file
            process->argc -= 2; // Adjust argument count for each redirection found
        } else {
            current = current->next; // Move to the next token if not a redirection
        }
    }
    return head;
}

int count_pipes(t_list *tokens) 
{
    int pipe_count = 0;
    while (tokens != NULL) {
        if (strcmp(tokens->content, "|") == 0) {
            pipe_count++;
        }
        tokens = tokens->next;
    }
    return pipe_count;
}

t_process *process_init(t_list *token, int token_count, int index, t_prompt *prompt)
{
    t_process *process = safe_malloc(sizeof(t_process), prompt->shell);
    	process->index = index;
    process->argc = token_count;
    process->infile = infile_list_init(token, \
					process, prompt->shell);
	process->outfile = outfile_list_init(token, \
					process, prompt->shell);
    process->args = safe_malloc((token_count + 1) * sizeof(char *), prompt->shell);
    t_list *current_token = token;
    for (int i = 0; i < token_count; i++, token = token->next)
    {
        process->args[i] = strdup(token->content);
    }
    process->args[token_count] = NULL;
    if (process->args && process->args[0])
        process->command = strdup(process->args[0]);
    process->fd[0] = -1;
	process->fd[1] = -1;
    process->pid = -1;
    process->return_status = 0;
    process->prompt = prompt;
    process->shell = prompt->shell;
    return process;
}

t_prompt *prompt_init(char *line, t_list *token, t_shell *shell) {
    t_prompt *prompt = safe_malloc(sizeof(t_prompt), shell);
    prompt->user_input = line;
    prompt->token = token;
    prompt->process_count = count_pipes(token) + 1;
    prompt->process = safe_malloc(prompt->process_count * sizeof(t_process *), shell);
    prompt->shell = shell;
    t_list *current = token;
    int process_index = 0;
    int token_count = 0;
    t_list *start = token; // Initialize start at the beginning of the token list

    while (current) {
        if (strcmp(current->content, "|") == 0 || !current->next) {
            // Include the current token if it's not a pipe
            int actual_token_count = strcmp(current->content, "|") == 0 ? token_count : token_count + 1;
            prompt->process[process_index] = process_init(start, actual_token_count, process_index, prompt);
            process_index++;
            token_count = 0; // Reset token count for the next process
            if (current->next) start = current->next; // Set start to the next token after the pipe
        } else {
            token_count++;
        }
        current = current->next;
    }
    if (prompt->process_count > 0 && prompt->process[prompt->process_count - 1]) {
        prompt->last_exit = prompt->process[prompt->process_count - 1]->return_status;
    } else {
        prompt->last_exit = -1;
    }
    return prompt;
}
