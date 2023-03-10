#ifndef GLOBAL_H
# define GLOBAL_H

// e libft?
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

//per far girare sigaction
//#define _POSIX_C_SOURCE 199309L
#define _POSIX_C_SOURCE 200809L

// Constant declarations
# define NAME_MAX 255
# define PATH_MAX 1024

# define PROMPT "\033[1;31mminisHELL$:\033[0m "

//per far funzionare rl_replace_lline
extern void	rl_replace_line(const char *text, int clear_undo);
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
	char				**words_operators;
	char				*command;
	char				**flags;
	char				**arguments;

	int		ret;

	struct s_command 	*next;
	struct s_command 	*prev;

	t_hellmini 			*shell;
}	t_command;

//tokenizer.c
int						tkn_nbr(char *str);
int						ft_strchr_len(char *str, char c);
t_command				* count_pqwq(t_command *command, char *str);
char					**rip_and_tear(t_command *command, char *str);

//expander.c
void					free_arr(char **split_arr);
char					**ft_arrdup(char **arr);
char					*exp_tkn(char *str, char **env);

//env_handlers.c
void					init_shell_env(char **pr_env, t_hellmini shell);

//signals.c
void					ft_suppress_output(void);
void					sigint_handler(int sig);
void					sigquit_handler(int sig);
void					sigquit_macro(int sig, t_hellmini *shell);
void					*ft_handler(int sig);
void					ft_sigs_handler(int sig);
#endif
