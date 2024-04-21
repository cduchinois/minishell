/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:35:10 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:47:41 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_digilen(int n)
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

int	ft_printnbr(int n)
{
	int	l;

	if (n == -2147483648)
	{
		ft_printstr("-2147483648");
		return (11);
	}
	l = ft_digilen(n);
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd ('-', 1);
		ft_putnbr_fd(n, 1);
	}
	else if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', 1);
	else
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putchar_fd(n % 10 + '0', 1);
	}
	return (l);
}
