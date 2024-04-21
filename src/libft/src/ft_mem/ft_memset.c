/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:52:26 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
/*fills  the  first  n  bytes of the memory area
pointed to by s with the constant byte c.
returns a pointer to the memory area s.*/
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		ptr[n - 1] = c;
		n--;
	}
	return (s);
}
