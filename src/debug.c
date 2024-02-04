// To delete, only for debugging purposes 
#include "../inc/minishell.h"
#include <stdio.h>

void    print_shell(t_shell *shell)
{
    int i = 0;

    ft_printf("____SHELL______\n");
    while (shell->env[i])
    {
        ft_printf("%s\n", shell->env[i]);
        i++;
    }
    ft_printf("exit = %d \n", shell->exit);
    ft_printf("exit_status = %d \n",shell->exit_status);
    ft_printf("pid = %d \n",shell->pid);
    ft_printf("sigquit = %d \n",shell->sigquit);
    ft_printf("sigint = %d \n",shell->sigint);
    ft_printf("__________________________\n");
    //print_prompt(shell->prompt);
}

void    print_prompt(t_prompt *prompt)
{
    ft_printf("_____PROMPT_____\n");
    ft_printf(" USER INPUT : %s \n ", prompt->user_input);
    int i = 0;
    while (prompt->tokens[i])
    {
        printf("token %d : %s --- ", i, prompt->tokens[i]);
        i++;
    }
    printf("\nPROCESS COUNT : %d\n", prompt->process_count);
    printf("INFILE : %s\n", prompt->infile);
    printf("OUTFILE : %s\n", prompt->outfile);
    printf("HEREDOC : %d\n", prompt->here_doc);
    printf("APPEND MODE: %d\n", prompt->append_mode);
    printf("last_exit: %d\n", prompt->last_exit);
    i = 0;
    while (i < prompt->process_count)
    {
        print_process(prompt->processes[i]);
        i++;
    }
}

void print_process(t_process *process)
{
    ft_printf("_____PROCESS %d_____\n", process->index);
    ft_printf(" COMMAND : %s \n ", process->command);
    ft_printf(" ARGC : %d \n ", process->argc);
    ft_printf(" FD IN : %d \n ", process->fd[0]);
    ft_printf(" FD OUT : %d \n ", process->fd[1]);
    int i = 0;
    while (process->args && process->args[i] != 0)
    {
        ft_printf("ARGUMENT %d : %s | DELIMITER : %d | \n ",i, process->args[i], process->delimiters[i]);
        i++;
    }
}

void mini_parser(t_shell *shell, char *line)
{
    shell->prompt = malloc(sizeof(t_prompt));
    shell->prompt->user_input = line;
    shell->prompt->tokens = ft_split(line, ' ');
    shell->prompt->env = shell->env;
    shell->prompt->here_doc = false;
    shell->prompt->append_mode = false;
    shell->prompt->infile = NULL;
    shell->prompt->outfile = NULL;
    shell->prompt->last_exit = 0;
    shell->prompt->process_count = 1;
    shell->prompt->processes = NULL;
    shell->prompt->shell = shell;
    int i = 0;
    while (shell->prompt->tokens[i])
    {
        if (shell->prompt->tokens[i][0] == '|')
            shell->prompt->process_count++;
        i++;
    }
    i = 0;
    int n = -1;
    int j = 0;
    shell->prompt->processes = malloc(sizeof(t_process *) * shell->prompt->process_count + 1);
    shell->prompt->processes[j] = malloc(sizeof(t_process));
    shell->prompt->processes[j]->args = malloc(sizeof(char *) * 100);
    shell->prompt->processes[j]->delimiters = malloc(sizeof(int) * 100);
    shell->prompt->processes[j]->index = 0;
    shell->prompt->processes[j]->prompt = shell->prompt;
    shell->prompt->processes[j]->shell = shell;
    shell->prompt->processes[j]->pid = 0;

    while (shell->prompt->tokens[i])
    {
        if (shell->prompt->tokens[i][0] == '|')
        {
            n = -1;
            i++;
            j++;
            shell->prompt->processes[j] = malloc(sizeof(t_process));
            shell->prompt->processes[j]->index = j;
            shell->prompt->processes[j]->prompt = shell->prompt;
            shell->prompt->processes[j]->shell = shell;
            shell->prompt->processes[j]->pid = 0;
            shell->prompt->processes[j]->args = malloc(sizeof(char *) * 100);
            shell->prompt->processes[j]->delimiters = malloc(sizeof(int) * 100);
        }
        shell->prompt->processes[j]->argc = n + 1;
        if (n == -1)
        {
            shell->prompt->processes[j]->command = shell->prompt->tokens[i];
            shell->prompt->processes[j]->fd[0] = STDIN_FILENO;
            shell->prompt->processes[j]->fd[1] = STDOUT_FILENO;
            n++;
        }
        else
        {
            shell->prompt->processes[j]->args[n] = shell->prompt->tokens[i];
            shell->prompt->processes[j]->delimiters[n] = 0;
            n++;
        }
        i++;
    }
}
