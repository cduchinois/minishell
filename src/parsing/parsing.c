/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:36:13 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/20 11:03:20 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"





void	parse_line(t_shell *shell, char *line)
{
	char	*input;
	t_list	*token;

	input = ft_strdup(line);
	token = ft_strtoken(input, shell);
	if (!token)
	{
		shell->prompt = NULL;
		return ;
	}
	shell->prompt = prompt_init(token, shell);
}