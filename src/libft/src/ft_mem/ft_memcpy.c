/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:52:19 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
/*copies  n bytes from memory area src to memory area dest.
*The memory areas must not overlap.  Use memmove(3)  
*if  the memory areas do overlap - chevauchement.*/
{
	char	*s;
	char	*d;

	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (0);
	while (n > 0)
	{
		d[n - 1] = s[n - 1];
		n--;
	}
	return ((void *)dst);
}
