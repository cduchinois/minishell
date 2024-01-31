/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:17:36 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/04 18:33:28 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_end(char *line, char *stash)
{
	char	*end;

	if (!line || !stash || ft_strlen(line) == ft_strlen(stash))
	{
		free (stash);
		return (NULL);
	}
	end = malloc (ft_strlen(stash) - ft_strlen(line) + 1);
	if (!end)
		return (NULL);
	ft_strcpy(end, &stash[ft_strlen(line)]);
	free (stash);
	return (end);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{	
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	line = malloc (sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strncpy(line, str, i);
	line[i] = '\0';
	return (line);
}

void	read_and_stash(int fd, char **stash)
{
	char	*buf;
	char	*temp;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		if (*stash)
			temp = ft_strjoin(*stash, buf);
		else
			temp = ft_strdup(buf);
		free(*stash);
		*stash = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stash (fd, &stash);
	if (!stash)
		return (NULL);
	line = ft_line(stash);
	stash = ft_end(line, stash);
	return (line);
}
