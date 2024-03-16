// To delete, only for debugging purposes 
#include "../inc/minishell.h"


void print_env(t_lst_env *env_list)
{
    t_lst_env *current = env_list;
    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
void    print_shell(t_shell *shell)
{
    int i = 0;

    printf("____SHELL______\n");
    print_env(shell->env);
    printf("exit = %d \n", shell->exit);
    printf("exit_status = %d \n",shell->exit_status);
    printf("pid = %d \n",shell->pid);
    // printf("sigquit = %d \n",shell->sigquit);
    // printf("sigint = %d \n",shell->sigint);
    printf("__________________________\n");
    if (shell->prompt) {
        print_prompt(shell->prompt);
    } else {
        printf("No current prompt.\n");
    }
}

void    print_prompt(t_prompt *prompt)
{
    printf("_____PROMPT_____\n");
    printf(" USER INPUT : %s \n ", prompt->user_input);
    int i = 0;
    while (prompt->tokens[i])
    {
        printf("token %d : %s --- ", i, prompt->tokens[i]);
        i++;
    }
    printf("\nPROCESS COUNT : %d\n", prompt->process_count);
    printf("last_exit: %d\n", prompt->last_exit);
    i = 0;
    while (i < prompt->process_count)
    {
        print_process(prompt->process[i]);
        i++;
    }
}

void print_process(t_process *process)
{
    printf("_____PROCESS %d_____\n", process->index);
    printf("COMMAND: %s\n", process->command ? process->command : "NULL");
    printf(" ARGC : %d \n ", process->argc);
    printf(" FD IN : %d \n ", process->fd[0]);
    printf(" FD OUT : %d \n ", process->fd[1]);
    t_lst_infile *infile_temp = process->infile;
    while (infile_temp)
    {
        printf("infile %s; here_doc %d\n", infile_temp->name, infile_temp->here_doc);
        infile_temp = infile_temp->next;
    }

    t_lst_outfile *outfile_temp = process->outfile;
    while (outfile_temp)
    {
        printf("outfile %s; append_mode %d\n", outfile_temp->name, outfile_temp->append_mode);
        outfile_temp = outfile_temp->next;
    }
    for (int i = 0; process->args && process->args[i]; i++) {
        printf("arg[%d]: %s\n", i, process->args[i]);
    }
}

/*void mini_parser(t_shell *shell, char *line)
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
}*/
