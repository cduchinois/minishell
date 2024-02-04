// To delete, only for debugging purposes 
#include "../inc/minishell.h"
#include <stdio.h>
void    print_shell(t_shell shell)
{
    int i = 0;

    printf("___SHELL______\n");
    printf("Process count : %d \n", shell.process_count);
    //while (shell.env[i])
    //{
        //printf("env %d: %s \n", i, shell.env[i]);
        //i++;
    //}
    //printf("pid : %d \n", shell.pid[0]);
    i = 0;
    while (i < shell.process_count)
    {
        print_process(shell.processes[i]);
        i++;
    }
}

void    print_process(t_process *process)
{
    int i = 0;
    printf("___PROCESS %d______\n", process->index);
    printf("command : %s \n", process->command);
    printf("pathname : %s \n", process->pathname);
    printf("infile %s \n", process->infile);
    printf("outfile %s \n", process->outfile);
    printf("heredoc %d \n", process->here_doc);
    printf("appendmode %d \n", process->append_mode);
    printf("fd in %d \n", process->fd[0]);
    printf("fd out %d \n", process->fd[1]);
    while (process->args[i])
    {
        printf("args %d : %s \n", i, process->args[i]);
        i++;
    }
}