/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:40:56 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:54:03 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_digilen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		return (ft_digilen(-n) + 1);
	else if (n >= 0 && n < 10)
		return (1);
	else
	{
		while (n > 0)
		{
			n /= 10;
			i++;
		}
		return (i);
	}
}

void	ft_affdigit(int n, char **str, size_t len)
{
	(*str)[len] = '\0';
	if (n < 0)
	{
		(*str)[0] = '-';
		n *= -1;
	}
	if (n == 0)
		(*str)[0] = '0';
	while (n > 0 && len > 0)
	{
		(*str)[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*c;
	int		l;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	l = ft_digilen(n);
	c = malloc(sizeof(char) * (l + 1));
	if (!c)
		return (0);
	ft_affdigit(n, &c, l);
	return (c);
}
