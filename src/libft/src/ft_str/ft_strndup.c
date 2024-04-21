/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:13:42 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 13:56:09 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*tab;
	int		i;

	i = 0;
    if (!s)
    {
        return (0);
    }
	tab = malloc(sizeof(char) * (n + 1));
	if (!tab)
		return (0);
	while (i < n)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
