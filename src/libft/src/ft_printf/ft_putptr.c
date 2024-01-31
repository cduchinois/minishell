/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:35:10 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:47:53 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_ptrlen(unsigned long long n)
{
	int	i;

	i = 0;
	if (n < 16)
		return (3);
	else
	{
		while (n > 0)
		{
			n /= 16;
			i++;
		}
	}
	return (i + 2);
}

int	ft_putull(unsigned long long n)
{
	char	*str;

	str = "0123456789abcdef";
	if (n < 16)
		ft_putchar_fd(str[n], 1);
	else
	{
		ft_putull(n / 16);
		ft_putchar_fd(str[n % 16], 1);
	}
	return (ft_ptrlen(n));
}

int	ft_putptr(unsigned long long n)
{	
	if (n == 0)
		return (ft_printstr("(nil)"));
	ft_printstr ("0x");
	ft_putull(n);
	return (ft_ptrlen(n));
}
