#ifndef GLOBAL_H
# define GLOBAL_H

// e libft?
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

// Constant declarations
# define NAME_MAX 255
# define PATH_MAX 1024

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 		**env;

	int			*exit_status;
	struct s_command 	*current_cmd;


    pid_t 		pid; // maybe
}           t_hellmini;

//words_operators e'la prima splittata(" ")dell'input, ergo la prima tokenizzazione;
//potrebbe servirne una ulteriore per semplificare la lettura del codice(in generale ma
//soprattutto in presenza di < > << >>)
typedef struct s_command
{
	char	**words_operators;
	char	*command;
	char	**flags;
	char	**arguments;
	int		mc_pipes;
	int		mc_quotes;
	int		mc_wquotes;

	int		ret;

	struct s_command *next;
	struct s_command *prev;

	t_hellmini *shell;
}	t_command;

//tokenizer.c
//
//
//
t_command	* count_pqwq(t_command *command, char *str);
int			rip_and_tear(t_command *command, char *str);
#endif
