/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgranger <fgranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:34:10 by yuewang           #+#    #+#             */
/*   Updated: 2024/02/04 17:09:41 by fgranger         ###   ########.fr       */
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
# include <limits.h>
# include <stdbool.h>

//PATH_MAX define value to be checked for linux the define on mac is 1024 and 260 on PC 

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

// Define the process structure
/*
    Structure that containsall the data required for executing the current command
    int index; index of the current command starting from 0
    char * command name of the command, the existence and assignement (builtins or not) will be checked at execution
    int argc number of argument after the command (example : echo hello == 1)
    char **args array of strings with each instructions (echo -n hello == {"-n", "hello"})
    int fd[2] == fd[0] init with STDIN and fd[1] init with STDOUT (All redirection (file in or out will be managed during exec))
    char **env env variable from prompt or shell
    int *delemiter the delimiter is the same size as the args for each args I need to know how it was find (between quotes, single quotes or nothing)
        THe int delimiter array values are stated in enum delimiter
*/

enum delimiter
{
    DQUOTES,
    SQUOTES,
    NOTHING
};

typedef struct s_process
{
    char **env; 
    int index;
    char *command;
    int argc;
    char **args;
    int *delimiter;
    char *infile;
    char *outfile;
    int fd[2];
} t_process;

//Define the current prompt structure 
/*
    Structure that initiated after each user input (readine)
    the structure contains all informations requiered to execute the prompt
        char *user_input that is the raw input read by readline
        char **tokens which is the split of the raw input per instruction either space (one or more) or the quotes
        int process_count which is going to indicate the number of processes to be executed 1 + number of pipes
        char **env that from the shell structure
        t_process *processes contains an array of the processes to be executed
        int process_index to be initialized to 0 will be used during execution
        int last_exit to be initialized to 0 will be completed during each exec of the prompt
        char * infile only if infile is set else init to NULL
        char * outfile only if outfile is set else init to NULL
        bool here_doc always set to false except in case of heredoc // another struct should be added later on to manage expansion of here do and delimiter
        bool append_mode always init to false except in case of append outfile
*/

typedef struct s_prompt
{
    char *user_input;
    char **tokens;
    int process_count;
    char **env;
    char *infile;
    char *outile;
    bool here_doc;
    bool append_mode; 
    t_process *processes;
    int process_index;
    int last_exit;
} t_prompt;

// Define the shell structure
/*
    Structure initialized once at the start of program with variable used for the scope of shell itself
    char **env; get env from main 
    bool exit; set to false will be modified in case of exit command
    t_prompt prompt current prompt being executed / Last prompt
    int_last_exit_code to be init to 0;
    Other variable to be set later on 
*/
typedef struct s_shell 
{
    char **env;
    t_prompt *prompt;
    bool exit;
    int last_exit_code;
} t_shell;

//To delete only for debuggin purposes
void    print_process(t_process *process);
void    print_shell(t_shell shell);
//_________________________________________

char **ft_strtoken(char *input);
int ft_isredirection(char *s);

t_shell *init_struct_shell(char **tokens, char *envp[]);
void ft_fd_in(int i, t_process **processes);
void ft_fd_out(int i, t_process **processes, int process_count);
char	*get_pathname(char **env, char *command);
void	ft_execute(t_shell *shell);

// Built-in functions 
int ft_echo(char **args);
int ft_pwd(void);
int ft_env(char **env, int argc);

#endif