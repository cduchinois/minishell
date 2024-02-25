#include "../inc/minishell.h"

int ft_exit(t_process *process)
{
    ft_printf("exit to be coded\n");
    exit(process->shell->exit_status);
}