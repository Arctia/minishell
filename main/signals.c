#include "../global.h"
//Ctrl-C
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
//Ctrl-D
void	sigquit_handler(int sig)
{

	//ft_putstr_fd("exit\n", 1);
	//write(1, "exit\n", 6);
	(void)sig;
	// write(1, "exit\n", 6);
	rl_on_new_line();
	rl_redisplay();
	exit(0);
}
//Ctrl-D migliorato?
void	sigquit_macro(int sig, t_hellmini *shell)
{
	char *exit_msg;

	exit_msg = NULL;
	//exit_msg = ft_strjoin(PROMPT, "exit\n");
	if (!sigaction(SIGQUIT, NULL, NULL))
	{
		exit_msg = ft_strjoin(PROMPT, "exit\n");
		shell->input = readline(exit_msg);
	}
	free(exit_msg);
	sigquit_handler(sig);
}
//per i children?serve?
