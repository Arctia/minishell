#include "../global.h"

void	ft_sigs_handler(int sig)
{
	// struct sigaction sa;

	// sa.sa_flags = SA_SIGINFO;
	// sa.sa_sigaction = ft_handler(sig);


	//char tmp_buf[4095];
	if (sig == SIGINT)
	{
		(void)sig;
		write(1, "\n", 1);
		ft_suppress_output();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	// if (sig == SIGQUIT)
	// {
	// 	(void)sig;
	// 	// waitpid(- 1, NULL, WUNTRACED);
	// 	rl_replace_line("exit", 0);
	// 	rl_redisplay();
	// 	exit(0);
	// }
	//return(0);
}
