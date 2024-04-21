/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:57:42 by fgranger          #+#    #+#             */
/*   Updated: 2024/04/21 13:22:27 by fgranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_here_doc(char *delimiter, int i, t_prompt *prompt)
{
	int		fd_infile;
	char	*line;

	fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile < 0)
		return (exec_error2(prompt->process[i], strerror(errno),
				errno, prompt->process[i]->pid), -1);
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

static int set_infile_bt(t_lst_file *file, int i, t_prompt *prompt)
{
    int fd, tmp_in;

    tmp_in = dup(STDIN_FILENO);
    if (tmp_in == -1) {
        return exec_error2(prompt->process[i], strerror(errno), errno, prompt->process[i]->pid);
    }

    if (file->mode == 1)
        fd = handle_here_doc(file->name, i, prompt);
	else
        fd = open(file->name, O_RDONLY);  

    if (fd == -1) {
        close(tmp_in);
        return exec_error2(prompt->process[i], strerror(errno), errno, prompt->process[i]->pid);
    }
    close(tmp_in);

    return EXIT_SUCCESS;
}

static int set_outfile_bt(t_lst_file *file, int i, t_prompt *prompt)
{
    int fd;
    fd = open(file->name, file->mode, 0644);
    if (fd == -1)
	{
        exec_error2(prompt->process[i], strerror(errno), 1, prompt->process[i]->pid);
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return 0;
}

void	ft_set_pipes(t_prompt *prompt, int i)
{
	if (i != 0)
	{
        // printf("dup stdin->lastpipefd:%d\n", prompt->last_pipe_fd);
        dup2(prompt->last_pipe_fd, STDIN_FILENO);
		close(prompt->last_pipe_fd);
	}
	if (i != prompt->process_count - 1)
	{
        // printf("dup stdout->shellfd[1]:%d\n", prompt->shell->fd[1]);
		dup2(prompt->shell->fd[1], STDOUT_FILENO);
	}
	close(prompt->shell->fd[1]);
	close(prompt->shell->fd[0]);
}

static	int	set_infile(t_lst_file *file, int i, t_prompt *prompt)
{
	int	fd;
	int	tmp_in;

	tmp_in = dup(STDIN_FILENO);
	if (file && file->mode == 1)
	{	
		// printf("setinfile_heredoc:copystdin");
        dup2(tmp_in, STDIN_FILENO);
		fd = handle_here_doc(file->name, i, prompt);
	}
	else
		fd = open(file->name, O_RDONLY);
	close(tmp_in);
	if (fd == -1)
	{
		return (exec_error2(prompt->process[i], strerror(errno), 1, prompt->process[i]->pid));
	}
	dup2(fd, STDIN_FILENO);
    // printf("setinfile->fd:%d\n", fd);
	close(fd);
	return (EXIT_SUCCESS);
}

static int set_outfile(t_lst_file *file, int i, t_prompt *prompt)
{
    int fd;
    fd = open(file->name, file->mode, 0644);
    if (fd == -1)
	{
        exec_error2(prompt->process[i], strerror(errno), 1, prompt->process[i]->pid);
        return 1;
    }
    dup2(fd, STDOUT_FILENO);
    // printf("setoutfile->fd:%d\n", fd);
    close(fd);
    return 0;
}

int ft_set_files(t_prompt *prompt, int i) {
    t_lst_file *file = prompt->process[i]->file;

    while (file) {
        // Handling input files
        if (file->type == 0) {
            if (set_infile(file, i, prompt) != EXIT_SUCCESS) {
                // Handle error, maybe print an error message
                return 1;
            }
        }
        // Handling output files
        else if (file->type == 1) {
            if (set_outfile(file, i, prompt) != EXIT_SUCCESS) {
                // Handle error, maybe print an error message
                return 1;
            }
        }
        file = file->next;
    }
    return EXIT_SUCCESS;
}

int ft_set_files_bt(t_prompt *prompt, int i)
{
    t_lst_file *file = prompt->process[i]->file;
    // t_lst_outfile *outfile = prompt->process[i]->outfile;

    while (file) {
        // Handling input files
        if (file->type == 0) {
            if (set_infile_bt(file, i, prompt) != EXIT_SUCCESS) {
                // Handle error, maybe print an error message
                return 1;
            }
        }
        // Handling output files
        else if (file->type == 1)
        {
            if (set_outfile_bt(file, i, prompt) != EXIT_SUCCESS) {
                // Handle error, maybe print an error message
                return 1;
            }
        }
        file = file->next;
    }
    return EXIT_SUCCESS;
}


