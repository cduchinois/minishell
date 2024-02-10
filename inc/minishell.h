/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:34:10 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/10 15:24:20 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "structs.h" 
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
# include <limits.h>
# include <stdbool.h>

//PATH_MAX define value to be checked for linux the define on mac is 1024 and 260 on PC 

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

//To delete only for debuggin purposes
void    print_process(t_process *process);
void    print_prompt(t_prompt *prompt);
void    print_shell(t_shell *shell);
void mini_parser(t_shell *shell, char *line);
void parse_line(t_shell *shell, char *line);
//_________________________________________

char **ft_strtoken(char *input, t_shell *shell); 
int ft_isredirection(char *s);

void init_shell(t_shell **shell, char **envp);
void ft_fd_in(int i, t_process **processes);
void ft_fd_out(int i, t_process **processes, int process_count);
char	*get_pathname(char **env, char *command);
void	ft_execute(t_prompt *prompt);

// Built-in functions 
int ft_echo(char **args);
int ft_pwd(void);
int ft_env(char **env, int argc);

//safe functions
void *safe_malloc(size_t size, t_shell *shell);
void clean(t_shell *shell); 


#endif