/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:12:22 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/04 11:19:39 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, l1 + l2 + 1);
	ft_strlcat(res, s2, l1 + l2 + 1);
	return (res);
}
