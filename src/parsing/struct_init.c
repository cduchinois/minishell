/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:24:05 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/21 02:21:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// typedef struct s_lst_file
// {
// 	int type;//0=infile; 1=outfile
// 	int mode;//infile:1=here_doc
// 	char *name;
// 	struct s_lst_file *next;
// } t_lst_file;

// typedef	struct s_process
// {
// 	t_lst_file *file;
// 	// t_lst_outfile *outfile;
// 	t_prompt *prompt;
// 	t_shell *shell;
// } t_process;

t_lst_file	*create_file_node(const char *filename, int type, int mode, t_shell *shell)
{
	t_lst_file	*node;

	node = (t_lst_file *)safe_malloc(sizeof(t_lst_file), shell);
	node->name = strdup(filename);
	node->type = type;
	node->mode = mode;
    node->next = NULL;
	return (node);
}

void	append_file_node(t_lst_file **head, t_lst_file *new_node)
{
	t_lst_file	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

t_lst_file *file_list_init(t_list *start, t_process *process, t_shell *shell)
{
    t_lst_file *head = NULL;
    t_list *current = start;
    int mode;

    while (current && current->next && strcmp(current->content, "|") != 0)
    {
        if (ft_strcmp(current->content, "<") == 0 || ft_strcmp(current->content, "<<") == 0)
        {
            if (strcmp(current->content, "<<") == 0)
                mode = 1;
            else
                mode = 0;            
            t_lst_file *new_node = create_file_node(current->next->content, 0, mode, shell);
            if (new_node)
                append_file_node(&head, new_node);
            current = current->next->next;
            process->argc -= 2;
        }
        else if (ft_strcmp(current->content, ">") == 0 || ft_strcmp(current->content, ">>") == 0)
        {
            if (strcmp(current->content, ">>") == 0)
                mode = O_WRONLY | O_CREAT | O_APPEND;
            else
                mode =  O_WRONLY | O_CREAT | O_TRUNC;      
            t_lst_file *new_node = create_file_node(current->next->content, 1, mode, shell);
            if (new_node)
                append_file_node(&head, new_node);
            current = current->next->next;
            process->argc -= 2;
        }
        else
        {
            current = current->next; // Move to the next token if not a redirection
        }
    }
    return head;
}

// t_lst_outfile *outfile_list_init(t_list *tokens, t_process *process, t_shell *shell) {
//     t_lst_outfile *head = NULL;
//     int append_mode = O_WRONLY | O_CREAT | O_TRUNC; 
//     t_list *current = tokens;

//     while (current && current->next && strcmp(current->content, "|") != 0) { // Ensure there's a token and a next token
//         if (strcmp(current->content, ">") == 0 || strcmp(current->content, ">>") == 0) {
//             append_mode = strcmp(current->content, ">>") == 0 ? O_WRONLY | O_CREAT | O_APPEND : O_WRONLY | O_CREAT | O_TRUNC;
//             t_lst_outfile *new_node = create_outfile_node(current->next->content, append_mode, shell);
//             if (new_node) {
//                 append_outfile_node(&head, new_node);
//             }
//             current = current->next->next; // Move past the redirection token and its file
//             process->argc -= 2; // Adjust argument count for each redirection found
//         } else {
//             current = current->next; // Move to the next token if not a redirection
//         }
//     }
//     return head;
// }

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

int count_arguments(t_list *token, t_shell *shell) {
    int count = 0;
    t_list *current = token;

    while (current) {

        //    ft_putstr_fd("Current token: ", 2);
        // ft_putstr_fd((char*)current->content, 2);
        // ft_putstr_fd("\n", 2);

        if (ft_isredir((char*)current->content)) {
            if (current->next) 
            { // Skip the next token if it's a filename
                current = current->next;
            } 
            else 
            {
                ft_putstr_fd("Redirection missing filename, please specify: ", 2);
                exit(2); // Exit if redirection symbol is not followed by a filename
            }
        } else {
            count++;
        }
        current = current->next;
    }
    return count;
}

char **extract_arguments(t_list *start, int argc, t_shell *shell) {
    char **args = safe_malloc((argc + 1) * sizeof(char *), shell);
    if (!args) return NULL;

    t_list *current = start;
    int i = 0;
    while (current && i < argc) {
        if (strcmp(current->content, "|") == 0) break;  // Stop at a pipe
        if (ft_isredir((char*)current->content)) {
            if (current->next) {
                current = current->next;  // Skip the filename associated with the redirection
            }
        } else {
            args[i] = ft_strdup((char*)current->content);
            if (args[i] == NULL) {  // Handle strdup failure
                while (i-- > 0) free(args[i]);  // Clean up previously allocated memory
                free(args);
                return NULL;
            }
            i++;
        }
        current = current->next;
    }
    args[i] = NULL;  // Null-terminate the array
    return args;
}

t_process *process_init(t_list *start, int token_count, int index, t_prompt *prompt)
{
    t_process *process = safe_malloc(sizeof(t_process), prompt->shell);
    ft_memset(process, 0, sizeof(t_process));
    process->index = index;
    process->argc = token_count;  // Assume all tokens are valid arguments, adjust if necessary
    process->file = file_list_init(start, process, prompt->shell);
    // process->outfile = outfile_list_init(start, process, prompt->shell);
    process->args = extract_arguments(start, token_count, prompt->shell);  // Extract arguments
    if (process->args && process->args[0]) {
        process->command = ft_strdup(process->args[0]);
    }
    process->fd[0] = -1;
    process->fd[1] = -1;
    process->pid = -1;
    process->return_status = 0;
    process->prompt = prompt;
    process->shell = prompt->shell;
    return process;
}

// prompt malloc
// 	char *user_input; -> get from line->NO MALLOC,freed after tokenization 
// 	t_list *token;
// 	t_process **process;
// 	t_shell *shell;


t_prompt *prompt_init(t_list *token, t_shell *shell)
{
    t_prompt *prompt = safe_malloc(sizeof(t_prompt), shell);
    prompt->token = token;
    prompt->process_count = count_pipes(token) + 1;
    prompt->process = safe_malloc(prompt->process_count * sizeof(t_process *), shell);
    prompt->shell = shell;

    t_list *current = token;
    t_list *start = token;
    int process_index = 0;
    int token_count = 0;

    while (current)
    {
        if (strcmp(current->content, "|") == 0 || !current->next)
        {
            int actual_token_count = token_count;
            if (!current->next && strcmp(current->content, "|") != 0) {
                actual_token_count++;
            }
            prompt->process[process_index] = process_init(start, actual_token_count, process_index, prompt);
            process_index++;
            token_count = 0;
            start = current->next;
        }
        else
        {
            token_count++;
        }
        current = current->next;
    }

    if (prompt->process_count > 0 && prompt->process[prompt->process_count - 1]) {
        prompt->last_exit = prompt->process[prompt->process_count - 1]->return_status;
    } else {
        prompt->last_exit = -1;  // Handle cases with no processes or initialization failures
    }
    prompt->backup_fd[0] = dup(STDIN_FILENO);
    prompt->backup_fd[1] = dup(STDOUT_FILENO);
    return prompt;
}



