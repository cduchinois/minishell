/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:13:42 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/24 17:19:12 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_count_word(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
			count++;
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
	}
	return (count);
}

unsigned int	ft_wordlen(char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**tab;

	int (i) = 0;
	int (k) = 0;
	if (!s)
		return (NULL);
	tab = malloc ((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[k] = ft_strndup(&s[i], ft_wordlen(&s[i], c));
			if (!tab[k])
				return (ft_freetab(tab), NULL);
			k++;
			i += ft_wordlen(&s[i], c);
		}
	}
	tab[k] = NULL;
	return (tab);
}
