/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:34:10 by yuewang           #+#    #+#             */
/*   Updated: 2024/04/01 17:09:30 by fgranger         ###   ########.fr       */
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
# include <signal.h>



//PATH_MAX define value to be checked for linux the define on mac is 1024 and 260 on PC 

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
//To delete only for debuggin purposes
extern int		g_signal;
void    print_process(t_process *process);
void    print_prompt(t_prompt *prompt);
void    print_shell(t_shell *shell);
void    mini_parser(t_shell *shell, char *line);
void    parse_line(t_shell *shell, char *line);

//parsing_________________________________________
t_list *ft_strtoken(char *input, t_shell *shell);
t_list *extract_token(char *input, int *index, t_shell *shell);
char *ft_expand_token(char *token, t_shell *shell);
t_list *handle_wildcard(char *token_str, t_shell *shell);
int find_start(char *input, int *index, bool *in_squote, bool *in_dquote);
int find_end(char *input, int *index, bool *squote, bool *dquote);
void trim_quote(char **token);
char	*handle_quotes(char *str, const char *token, int *i);

//files manipulation
t_lst_infile *create_infile_node(const char *filename, bool here_doc, t_shell *shell);
void append_infile_node(t_lst_infile **head, t_lst_infile *new_node);
t_lst_outfile *create_outfile_node(const char *filename, int append_mode, t_shell *shell);
void append_outfile_node(t_lst_outfile **head, t_lst_outfile *new_node);

char **extract_arguments(char **tokens, int argc, t_shell *shell);

t_prompt *prompt_init(char *line, t_list *token, t_shell *shell);

int ft_isredir(char *s);
int	ft_isquote(char s);

int ft_redirlen(char *s);


void init_shell(t_shell **shell, char **envp);
void ft_fd_in(int i, t_process **processes);
void ft_fd_out(int i, t_process **processes, int process_count);
void	ft_clear_fd(t_prompt *prompt, int sub);

//signal_________________________________________
void setup_signal_handlers();
void setup_signal_handlers_non_empty_line();

//Execution
int	ft_execute(t_prompt *prompt);
bool ft_is_builtin(char *cmd);
void ft_exec_builtin(t_process *process);
void ft_exec_process(t_process *process);

//redirection
void	ft_set_pipes(t_prompt *prompt, int i);
int     ft_set_files(t_prompt *prompt, int i);
	
// Built-in functions 
int ft_echo(char **args);
int ft_pwd(void);
int ft_env(t_lst_env *env, int argc);
int ft_export(t_process *process);
int ft_unset(t_process *process);
int ft_exit(t_process *process);
int ft_cd(t_process *process);
	
//safe functions
void *safe_malloc(size_t size, t_shell *shell);
void clean(t_shell *shell);
void free_prompt(t_prompt *prompt);

//env manipulation functions
void ft_free_env(t_lst_env *env);
char    *find_var_from_envp(t_lst_env *env, char *var_name);
t_lst_env *env_new_node(char *key, const char *value, bool export_only, t_shell *shell);
void env_append(t_lst_env **lst, t_lst_env *new_node);
char * ft_get_key(char *var);
t_lst_env *var_exist(t_lst_env *env, char *var);
int var_is_valid(char *var, int mode);
t_lst_env *ft_env_dup(t_lst_env *env, t_shell *shell);
int ft_print_sorted_env(t_lst_env *env, t_shell *shell);
int export_var(t_shell *shell, char *var);
char *get_pathname(t_lst_env *env, char *command);
int	ft_env_len(t_lst_env *env);

//error
int    exec_error(char *cmd, char *msg, int error, int ex, t_shell *shell);
#endif