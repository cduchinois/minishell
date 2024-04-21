/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:54:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:47:37 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_printchar(int c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_args(va_list args, const char c)
{
	if (c == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, unsigned long long)));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putuint(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(c, va_arg(args, unsigned int)));
	else if (c == '%')
		return (ft_printchar('%'));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		l;

	i = 0;
	l = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			l += ft_args(args, str[i]);
		}
		else
			l += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (l);
}
