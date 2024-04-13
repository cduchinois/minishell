/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:04:09 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/13 19:03:15 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void *safe_malloc(size_t size, t_shell *shell)
{
    void *allocated_mem;

    allocated_mem = ft_calloc(1, size);  // Allocate and zero-initialize
    if (!allocated_mem) {
        perror("malloc error");
        clean(shell);  // Ensure this cleanup function itself does not rely on uninitialized memory
        exit(EXIT_FAILURE);
    }
    return allocated_mem;
}

