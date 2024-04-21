/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:56:03 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 14:44:19 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	ft_home(t_process *process)
{
	char	*path_home;
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX + 1));
	path_home = find_var_from_envp(process->shell->env, "HOME");
	if (!path_home)
		return (EXIT_FAILURE);
	if (chdir(path_home))
		return (EXIT_FAILURE);
	pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX + 1));
	export_var(process->shell, pwd);
	export_var(process->shell, oldpwd);
	return (EXIT_SUCCESS);
}

static	int	ft_change_dir(t_process *process)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX + 1));
	if (!process->args[1])
		return (EXIT_FAILURE);
	if (chdir(process->args[1]))
    {
		
                ft_putstr_fd(" No such file or directory\n", 2);

		return (EXIT_FAILURE);
    }
    export_var(process->shell, oldpwd);
	pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX + 1));
	export_var(process->shell, pwd);
	return (EXIT_SUCCESS);
}

static	int	ft_back_to_old(t_process *process)
{
	char	*path_old;
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	errno = 0;
	oldpwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX + 1));
	path_old = find_var_from_envp(process->shell->env, "OLDPWD");
	if (!path_old)
		return (EXIT_FAILURE);
	if (chdir(path_old))
		return (EXIT_FAILURE);
	pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX + 1));
	export_var(process->shell, pwd);
	export_var(process->shell, oldpwd);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_process *process)
{
	int	error;

	if (process->argc > 2)
    {
                ft_putstr_fd(" too many arguments\n", 2);

		return (EXIT_FAILURE);
    }
    if (process->args[1])
	{
		if (!ft_strcmp(process->args[1], "-"))
			return (ft_back_to_old(process));
		else if (ft_change_dir(process))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	return (ft_home(process));
}
