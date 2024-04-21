/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:04:09 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 17:17:48 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*safe_malloc(size_t size, t_shell *shell)
{
	void	*allocated_mem;

	allocated_mem = malloc(size);
	if (!allocated_mem)
	{
		perror("malloc error");
		clean(shell);
	}
	return (allocated_mem);
}
