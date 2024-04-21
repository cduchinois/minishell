/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:05:21 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/04 11:17:44 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	int		j;

	len = ft_strlen(s);
	j = c % 256;
	if (c == 0)
		return ((char *)s + len);
	if (len == 1)
		return ((char *)s);
	while (len > 0)
	{
		if (s[len - 1] == j)
			return ((char *)s + len - 1);
		len--;
	}
	return (NULL);
}
