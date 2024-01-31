/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:19:44 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:53:03 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char	*s)
/*returns a pointer to a new string which is a duplicate of the string s.  
Memory for the new string  is  obtained  with malloc(3), 
and can be freed with free(3).*/
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tab)
		return (0);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
