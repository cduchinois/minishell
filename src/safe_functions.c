/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:04:09 by fgranger          #+#    #+#             */
/*   Updated: 2024/02/10 06:28:29 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void *safe_malloc(size_t size, t_shell *shell)
{
    void *allocated_mem;

    allocated_mem = malloc(size);
    if (!allocated_mem)
    {
        perror("malloc error");
        clean(shell);
        exit(EXIT_FAILURE);
    }
    return (allocated_mem);
}

