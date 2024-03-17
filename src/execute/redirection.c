/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:57:42 by fgranger          #+#    #+#             */
/*   Updated: 2024/03/17 20:29:17 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_set_pipes(t_prompt *prompt)
{
	int	i;

	i = 0;
	while (i < prompt->process_count)
	{
		if (pipe(prompt->process[i]->fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static int	handle_here_doc(char *delimiter, int i)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (-1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd_infile, line, ft_strlen(line));
		free(line);
	}
	close(fd_infile);
	return (open(".here_doc", O_RDONLY));
}

void set_infile(t_lst_infile *infile, const int *tmp_in, int i)
{
    int fd;
    
    if (infile && infile->here_doc)
    {	
        dup2(*tmp_in, STDIN_FILENO);
        fd = handle_here_doc(infile->name, i);
    }
    else
        fd = open(infile->name, O_RDONLY);
    if (fd == -1)
        exit(2);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void	set_fd(t_prompt *prompt, int i)
{
	int					fd;
	t_lst_infile	*infile;
	t_lst_outfile	*outfile;
	const int			tmp_in = dup(STDIN_FILENO);
    
    infile = prompt->process[i]->infile;
	while (infile)
	{
        set_infile(infile, &tmp_in, i);
		infile = infile->next;
	}
    outfile = prompt->process[i]->outfile;
	while (outfile)
	{
		fd = open(outfile->name, outfile->append_mode, 0644);
        if (fd == -1)
            exit(EXIT_FAILURE);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		outfile = outfile->next;
	}
}
