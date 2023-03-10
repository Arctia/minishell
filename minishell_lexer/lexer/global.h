#ifndef GLOBAL_H
# define GLOBAL_H

// e libft?
//# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
//# include <readline/readline.h>
//# include <readline/history.h>

// Constant declarations
# define NAME_MAX 255
# define PATH_MAX 1024

// Operator presence
# define PIPE 0
# define SQUOTE 1
# define DQUOTE 2
# define MQUOTE 3
# define REDIN 4
# define REDOUT 5
# define REDAPP 6
# define HERDOC 7
# define CASH 8

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 				**env;

	int					exit_status;
	char				*input;
	struct s_command	*current_cmd;
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
	char				**words_operators;
	char				*str;
	int					spc[9];
	char				*command;
	char				**flags;
	char				**arguments;
	int					exp;

	int		ret;

	struct s_command 	*next; 
	struct s_command 	*prev;

	t_hellmini 			*shell;
}	t_command;

//tokenizer.c
//int						tkn_nbr(char *str);
//int						ft_strchr_len(char *str, char c);
//t_command				* count_pqwq(t_command *command, char *str);
//char					**rip_and_tear(t_command *command, char *str);

//lexer
int     lexer_init(t_hellmini *shell);
//lexer_splitter
void	lexer_error(char *message);
char	*split_operator(char *line, int *ff);
char	*split_line(char *line);


//expander.c
//void					free_arr(char **split_arr);
//char					**ft_arrdup(char **arr);
//char					*exp_tkn(char *str, char **env);

//env_handlers.c
//void					init_shell_env(char **pr_env, t_hellmini shell);


#endif