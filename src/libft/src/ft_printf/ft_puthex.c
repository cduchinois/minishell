/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:35:10 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:47:49 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_hexlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n < 16)
		return (1);
	else
	{
		while (n > 0)
		{
			n /= 16;
			i++;
		}
		return (i);
	}
}

int	ft_puthex(char c, unsigned int n)
{
	char	*str;

	if (c == 'x')
		str = "0123456789abcdef";
	else if (c == 'X')
		str = "0123456789ABCDEF";
	else
		return (0);
	if (n < 16)
		ft_putchar_fd(str[n % 16], 1);
	else
	{
		ft_puthex(c, n / 16);
		ft_putchar_fd(str[n % 16], 1);
	}
	return (ft_hexlen(n));
}
