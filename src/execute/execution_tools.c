#include "../inc/minishell.h"

void ft_exec_builtin(t_process *process)
{
	if (ft_strcmp(process->command, "echo") == 0)
		process->prompt->last_exit = ft_echo(process->args);
	else if (ft_strcmp(process->command, "pwd") == 0)
		process->prompt->last_exit = ft_pwd();
	else if (ft_strcmp(process->command, "env") == 0)
		process->prompt->last_exit = ft_env(process->shell->env, 0);
	exit(process->prompt->last_exit);
}

bool ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	//other buit-ins to be added later on
	return (false);
}

void ft_exec_process(t_process *process)
{
	char *path;
	
    if (ft_is_builtin(process->command) == true)
		ft_exec_builtin(process);
	else
	{
		path = get_pathname(process->shell->env, process->command);
		execve(path, process->args, process->shell->env);
	}
}