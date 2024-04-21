/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:19:09 by yuewang           #+#    #+#             */
/*   Updated: 2023/12/19 13:24:29 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

/*les c ascii  représenter 2(7)=128 valeurs différentes, allant de 0 à 127.
puis pour representer les ecritures il y a l'ascii etendu jusqu'a 256 
ou encore d'autre encodage*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
