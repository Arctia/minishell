#include "../global.h"
//Ctrl-C
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_re_canon()
{
	struct termios	raw_settings;

	raw_settings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
						| INLCR | IGNCR | ICRNL | IXON);
	raw_settings.c_oflag &= ~OPOST;
	raw_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw_settings.c_cflag &= ~(CSIZE | PARENB);
	raw_settings.c_cflag |= CS8;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings);
	write(1, "gesuappeso\n", 12);
}


void	ft_suppress_output(void)
{
	struct termios	new_settings;
	struct termios	old_settings;

	tcgetattr(STDIN_FILENO, &new_settings);
	old_settings = new_settings;
	write(1, "dioladrobastardo\n", 18);
	ft_re_canon();
	// new_settings.c_lflag &= ~ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_settings);
	// write(1, "exit\n", 5);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &old_settings);
	exit(0);
}
//Ctrl-D
void	sigquit_handler(int sig)
{
	//int	ch_pid;

	//ch_pid = fork();
	//ft_putstr_fd("exit\n", 1);
	//write(1, "exit\n", 6);
	(void)sig;
	///waitpid(ch_pid, NULL, 0);
	// rl_on_new_line();
//	if (ch_pid)
	ft_suppress_output();
//		write(1, "exit\n", 6);
	//if (!tcdrain(STDOUT_FILENO))
	//exit(0);
	// rl_redisplay();

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
