/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:38:11 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/01 17:09:39 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_free_join(char *str, char *add)
{
	char	*tmp;

	if (!add || !str)
        return (NULL);
	tmp = str;
	str = ft_strjoin(tmp, add);
	free(tmp);
	return (str);
}

int    exec_error(char *cmd, char *msg, int error, int ex, t_shell *shell)
{
    char *full_msg;
    full_msg = ft_free_join(cmd, " : ");
    full_msg = ft_free_join(full_msg, msg);
    ft_putendl_fd(full_msg, STDERR_FILENO);
    free(full_msg);
    clean(shell);
    if (ex == 0 && error == EFAULT)
        exit (127);
    if (ex == 0)
        exit(errno);
    g_signal = 1;
    return (1);
}