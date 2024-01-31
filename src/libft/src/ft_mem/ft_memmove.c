/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:52:22 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
/*copies n bytes from memory src to dest.  
The memory areas may overlap
the bytes in src are first copied into a temporary array that does not
overlap src or dest, and the bytes are then copied from the temporary
array to dest.
RETURN a pointer to dest*/
{
	char	*s;
	char	*d;
	int		i;

	i = -1;
	if (!src && !dst)
		return (0);
	s = (char *)src;
	d = (char *)dst;
	if (s < d)
		while ((int)--n >= 0)
			d[n] = s[n];
	else
		while (++i < (int)n)
			*(d + i) = *(s + i);
	return ((void *)d);
}
