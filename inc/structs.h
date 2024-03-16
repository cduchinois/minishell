/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:22:37 by yuewang           #+#    #+#             */
/*   Updated: 2024/03/16 17:50:00 by yuewang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

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

enum error
{
	QUOTES,
	EMPTY,
	OUTFILE,
};

enum export_status
{
	UNVALID,
	EMPTY,
	VALID,
};

typedef struct s_prompt t_prompt;
typedef struct s_shell t_shell;
typedef struct s_lst_infile t_lst_infile;
typedef struct s_lst_outfile t_lst_outfile;
typedef struct s_lst_env t_lst_env;

typedef struct s_process
{
	int index;
	char *command;
	char *pathname;
	int argc;
	char **args;
	int *delimiters;
	int fd[2];
	int pid;
	int return_status;
	t_lst_infile *infile;
	t_lst_outfile *outfile;
	t_prompt *prompt;
	t_shell *shell;
} t_process;

//Define the current prompt structure 
/*
	Structure that initiated after each user input (readine)
	the structure contains all informations requiered to execute the prompt
		char *user_input that is the raw input read by readline
		char **tokens which is the split of the raw input per instruction either space (one or more) or the quotes
		int process_count which is going to indicate the number of processes to be executed 1 + number of pipes
		char **env that from the shell structure
		t_process **processes contains an array of the processes to be executed
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
	t_process **process;
	int process_count;
	// bool here_doc;
	// bool append_mode;
	int last_exit;
	t_shell *shell;
} t_prompt;

// Define the shell structure
/*
	Structure initialized once at the start of program with variable used for the scope of shell itself
	char **env; get env from main 
	t_prompt prompt current prompt being executed / Last prompt
	
	bool exit; set to false will be modified in case of exit command
	int exit_status init to 0 will be set with the last exit status recorded
	int pid set with current pid start at 0;
	int sigint signal management 
	int sigquit signal management
	Other variable to be set later on 
*/
typedef struct s_shell
{
	t_lst_env *env;
	t_prompt *prompt;
	bool exit;
	int exit_status;
	int pid;
	int error;
	// int sigint;
	// int sigquit;
} t_shell;

typedef struct s_lst_infile
{
	char *name;
	bool here_doc;
	struct s_lst_infile *next;
} t_lst_infile;

typedef struct s_lst_outfile
{
	char *name;
	int append_mode;
	struct s_lst_outfile *next;
} t_lst_outfile;

typedef struct s_lst_env
{
	char *key;
	char *value;
	bool    export_only;
	struct s_lst_env *next;
}  t_lst_env;

#endif
