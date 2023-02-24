#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

# define NAME_MAX 255
# define PATH_MAX 1024

typedef struct s_hellmini
{
	char **env;
	t_command *cmd; // we need it?
    pid_t pid;

}           t_hellmini;


typedef struct s_command
{
	char	args[2048][2048];
	char	rdr_in[2048][2048];		// <
	char	rdr_out[2048][2048];	// >
	char	heredoc[2048][2048];	// <<
	char	append[2048][2048];		// >>
	int		ret;		//return del comando
	int		err;		//errorno
}	t_command;


