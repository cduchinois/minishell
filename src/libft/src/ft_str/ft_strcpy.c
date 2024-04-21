/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:04:41 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 14:09:06 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
