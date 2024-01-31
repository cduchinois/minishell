/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:28:24 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:52:43 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		s = ft_calloc(1, sizeof(char *));
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
