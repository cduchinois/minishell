/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initiation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:36:13 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 14:31:10 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int count_pipes(char **tokens) 
{
    int pipe_count = 0;

    for (int i = 0; tokens[i] != NULL; i++) 
    {
        if (strcmp(tokens[i], "|") == 0) {
            pipe_count++;
        }
    }
    return pipe_count;
}

t_lst_infile *create_infile_node(const char *filename, bool here_doc, t_shell *shell)
{
    t_lst_infile *node = (t_lst_infile *)safe_malloc(sizeof(t_lst_infile), shell);
    node->name = strdup(filename);
    node->here_doc = here_doc;
    node->next = NULL;
    return node;
}

void append_infile_node(t_lst_infile **head, t_lst_infile *new_node)
{
    if (!head || !new_node) return;

    if (*head == NULL)
    {
        *head = new_node;
    } 
    else 
    {
        t_lst_infile *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

t_lst_infile *infile_list_init(char **tokens, int token_count, t_process *process, t_shell *shell)
{
    int i = 0;
    t_lst_infile *head = NULL;
    t_lst_infile *new_node;

    while (i < token_count) 
    {
        if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], "<<") == 0) && i + 1 < token_count)
        {
            new_node = create_infile_node(tokens[i + 1], ft_strcmp(tokens[i], "<<") == 0 ? true : false, shell);
            if (new_node)
                append_infile_node(&head, new_node);
            i += 2;
            process->argc -= 2;
        }
        else
            i++;
    }
    return head;
}

t_lst_outfile *create_outfile_node(const char *filename, bool append_mode, t_shell *shell)
{
    t_lst_outfile *node = (t_lst_outfile *)safe_malloc(sizeof(t_lst_outfile), shell);
    node->name = strdup(filename);
    node->append_mode = append_mode;
    node->next = NULL;
    return node;
}

void append_outfile_node(t_lst_outfile **head, t_lst_outfile *new_node) 
{
    if (!head || !new_node) return;

    if (*head == NULL)
    {
        *head = new_node;
    } 
    else
    {
        t_lst_outfile *current = *head;
        while (current->next) 
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

t_lst_outfile *outfile_list_init(char **tokens, int token_count, t_process *process, t_shell *shell)
{
    t_lst_outfile *head = NULL;
    int i = 0;

    while (i < token_count) 
    {
        if ((ft_strcmp(tokens[i], ">") == 0 || ft_strcmp(tokens[i], ">>") == 0) && i + 1 < token_count) 
        {
            bool append_mode = ft_strcmp(tokens[i], ">>") == 0 ? true : false;
            t_lst_outfile *new_node = create_outfile_node(tokens[i + 1], append_mode, shell);
            if (new_node) 
            {
                append_outfile_node(&head, new_node);
            }
            i += 2;
            process->argc -= 2;
        } 
        else
        {
            i++;
        }
    }
    return head;
}

char **extract_arguments(char **tokens, int argc, t_shell *shell)
{
    char **args = safe_malloc((argc + 1) * sizeof(char *), shell);
    int i = 0, j = 0; // i for tokens index, j for args index

    while (i < argc)
    {
        printf("debug extract token:processing token: %s\n", tokens[i]);
        if (ft_isredirection(tokens[i])) 
        {
            printf("Skipping redirection: %s %s\n", tokens[i], tokens[i+1]);            
            i += 2;
        } 
        else 
        {
            args[j] = ft_strdup(tokens[i]);
            printf("Adding arg[%d]: %s\n", j, args[j]); // Debug print
            //handle strdup failure
            j++;
            i++;
        }
    }
    args[j] = NULL;
    return args;
}

t_process *process_init(char **tokens, int token_count, int index, t_shell *shell)
{
    t_process *process = safe_malloc(sizeof(t_process), shell);
    process->index = index;
    process->argc = token_count;
    process->infile = infile_list_init(tokens, token_count, process, shell);
    process->outfile = outfile_list_init(tokens, token_count, process, shell);
    process->args = extract_arguments(tokens, process->argc, shell);
    printf("Extracted arguments:\n");
    for (int k = 0; process->args[k] != NULL; k++) {
        printf("arg[%d] %s\n", k, process->args[k]);
    }
    if (process->args && process->args[0])
        process->command = ft_strdup(process->args[0]);
    printf("Command: %s\n", process->command ? process->command : "NULL");
    process->pathname = get_pathname(shell->env, process->command);
    process->fd[0] = -1;
    process->fd[1] = -1;
    process->pid = -1;
    process->return_status = 0;
    process->prompt = shell->prompt;
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
        prompt->process[i] = process_init(&tokens[start], end - start, i, shell);
        if (!prompt->process[i]) 
        {
            clean(shell);
            exit(EXIT_FAILURE);
        }
        start = end + 1;
        i++;
    }
    prompt->last_exit = prompt->process[prompt->process_count - 1]->return_status;
    return (prompt);
}

void parse_line(t_shell *shell, char *line) 
{
    char **tokens = ft_strtoken(line, shell);
    for (int i = 0; tokens[i] != NULL; i++) 
        printf("Token %d: %s\n", i, tokens[i]);
    if (!tokens) return;
    shell->prompt = prompt_init(line, tokens, shell);
}
