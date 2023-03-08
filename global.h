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

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 		**env;

	int			*exit_status;
	struct s_command 	*cmd;
	char	*current_command;


    pid_t 		pid; // maybe 
}           t_hellmini;

typedef struct s_command
{
	char	*command;		//ls	//ls 	//cd
	char	**flags;		//la	//la	
	char	**arguments;					//..
	int		ret;
	char	*operator;			//|		//>		//>>
	int		export;



	struct s_command	*next;				//cd
	struct s_command *prev;

	struct s_hellmini *shell;
}	t_command;

#endif