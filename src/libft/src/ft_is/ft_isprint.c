/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:23:58 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*any printable character including space.
The ASCII values from 0 to 31 are reserved for control characters. 
These are non-printable characters that control various aspects of 
the communication and display 
but do not represent printable symbols or text. 
They include characters like the null character (0), line feed (10), 
carriage return (13), etc.
The ASCII value 127 is reserved for the DEL (delete) control character.
The ASCII values from 32 to 126 represent printable characters.
This range includes the space character (32), 
which is considered a printable character because it occupies space in text.*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
