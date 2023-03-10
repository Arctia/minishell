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

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 				**env;

	int					exit_status;
	char				*input;
	t_command 	        *com;
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
int	    check_argument(char *line, int i, char chr);
int     check_closures(char *line, int i, t_command *com);
int	    lexer(char *line, t_command *com);
char	lexer_start(char *line, t_command *com);
int     lexer_init(char *line);
//lexer_splitter
void	lexer_error(char *message, t_command *com);
int	    split_operator_line(char *line);
char	*split_operator(char *line);
char	*split_line(char *line);


//expander.c
//void					free_arr(char **split_arr);
//char					**ft_arrdup(char **arr);
//char					*exp_tkn(char *str, char **env);

//env_handlers.c
//void					init_shell_env(char **pr_env, t_hellmini shell);


#endif