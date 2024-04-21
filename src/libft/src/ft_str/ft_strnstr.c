/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:53:42 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
/*locates the first occurrence of the null-termi‐nated string little in the string big
where not more than len characters are searched.  
Characters that appear after a ‘\0’ character are not searched.  
If little is an empty string, big is returned; 
if little occurs nowhere in big, NULL is returned; 
otherwise a pointer to the first character of the first 
occurrence of little is returned.*/
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && big [i])
	{
		j = 0;
		if (big[i + j] == little[j])
		{
			while (big[i + j] == little[j] && i + j < len && \
			little[j] && big[i + j])
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
