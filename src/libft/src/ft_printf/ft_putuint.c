/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:35:10 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:47:57 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 0 && n < 10)
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

int	ft_putuint(unsigned int n)
{
	if (n < 10)
		ft_putchar_fd(n + '0', 1);
	else
	{
		ft_putnbr_fd(n / 10, 1);
		ft_putchar_fd(n % 10 + '0', 1);
	}
	return (ft_uintlen(n));
}
