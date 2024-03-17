/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 23:02:38 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/17 18:22:22 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, PATH_MAX + 1))
	{
		printf("%s\n", cwd);
		return (EXIT_SUCCESS);
	}
	perror("minishell:pwd:getcwd: ");
	return (EXIT_FAILURE);
}
