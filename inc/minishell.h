/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:34:10 by yuewang           #+#    #+#             */
/*   Updated: 2024/01/31 21:38:13 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../src/libft/inc/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Define the process structure
typedef struct s_process 
{
    int index;
    char *command;
    char *pathname;
    char **args;
    char *infile;
    char *outfile;
    int here_doc;
    int append_mode;
    int fd[2];
} t_process;

// Define the shell structure
typedef struct s_shell 
{
    int process_count;
    //char **history;
    char **env;
    t_process **processes;
    int *pid;
} t_shell;

char **ft_strtoken(char *input);
int ft_isredirection(char *s);

t_shell *init_struct_shell(char **tokens, char *envp[]);
void ft_fd_in(int i, t_process **processes);
void ft_fd_out(int i, t_process **processes, int process_count);
char	*get_pathname(char **env, char *command);
void	ft_execute(t_shell *shell);

#endif