/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 12:52:05 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_bzero(void *s, size_t n)
/*erases  the  data  in the n bytes of the memory
starting at the location pointed to by s
by writing zeros (bytes  con‐taining '\0')*/
{
	ft_memset(s, '\0', n);
}
