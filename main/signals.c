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
	(void)sig;
	write(1, "exit\n", 5);
	rl_on_new_line();
	rl_redisplay();
	exit(0);
}

//per i children?serve?
