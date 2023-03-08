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
# include <dirent.h>
# include <fcntl.h> //need it in master



// Constant declarations
# define NAME_MAX 255
# define PATH_MAX 1024

// Operator presence
# define PIPE	0
# define SQUOTE	1
# define DQUOTE	2
# define MQUOTE	3
# define REDIN	4
# define REDOUT	5
# define REDAPP	6
# define HERDOC	7
# define $$$$$$ 8

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 				**env;

	int					exit_status;
	char				*input;
	struct s_command 	*current_cmd;
	int					mc_pipes;
	int					mc_quotes;
	int					mc_wquotes;

//	pid_t				pid; // maybe
}           t_hellmini;

//words_operators e'la prima splittata(" ")dell'input, ergo la prima tokenizzazione;
//potrebbe servirne una ulteriore per semplificare la lettura del codice(in generale ma
//soprattutto in presenza di < > << >>)
typedef struct s_command
{
	char				**tokens;
	char				*str;
	int					spc[8];

	char				*command;
	char				**flags;
	char				**arguments;

	int		ret;

	struct s_command 	*next;
	struct s_command 	*prev;
	t_hellmini 			*shell;
}	t_command;