#include "../global.h"

//#define _POSIX_C_SOURCE 199309L#define _POSIX_C_SOURCE 199309L

// Ctrl-C(SIGINT)
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

//Ctrl-C 2.0(SIGINT)
void	sigint_help(char **envp)
{
	int		child;
	char	*cmd[3];

	cmd[0] =ft_strdup("stty");
	cmd[1] = ft_strdup("-echotcl");
	cmd[2] = "\0";
	child = fork();
	if (!child)
	{
		execve("/bin/stty", cmd, envp);
	}
	waitpid(child, NULL, 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// void	ft_re_canon()
// {
// 	struct termios	raw_settings;

// 	raw_settings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
// 						| INLCR | IGNCR | ICRNL | IXON);
// 	raw_settings.c_oflag &= ~OPOST;
// 	raw_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
// 	raw_settings.c_cflag &= ~(CSIZE | PARENB);
// 	raw_settings.c_cflag |= CS8;
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings);
// 	write(1, "gesuappeso\n", 12);
// }


void	ft_suppress_output(void)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &new_settings);
	//if (!tcgetattr(STDIN_FILENO, &new_settings))
	//old_settings = new_settings;
	//	write(1, "dioladrobastardo\n", 18);
	//ft_re_canon();
	new_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &new_settings);
	// write(1, "exit\n", 5);
	// if(!tcsetattr(STDOUT_FILENO, 0, &new_settings))
	// 	write(1,"bioparco\n", 10);
		//exit(0);
}
//Ctrl-D
void	sigquit_handler(int sig)
{
	int	ch_pid;

	ch_pid = fork();
	//ft_putstr_fd("exit\n", 1);
	//write(1, "exit\n", 6);
	(void)sig;
	waitpid(ch_pid, NULL, 0);
	// rl_on_new_line();
	// if (ch_pid)
	// 	rl_replace_line("exit\n", 0);
	//if (!tcdrain(STDOUT_FILENO))
	exit(0);
	// rl_redisplay();
}

//Ctrl-D migliorato?
// void	sigquit_macro(int sig, t_hellmini *shell)
// {
// 	struct sigaction sa;
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.__sigaction_u.__sa_sigaction = ft_handler;

// 	// if (!sigaction(SIGQUIT, NULL, NULL))
// 	// {
// 	// 	exit_msg = ft_strjoin(PROMPT, "exit\n");
// 	// 	shell->input = readline(exit_msg);
// 	// }
// 	// free(exit_msg);
// 	sigquit_handler(sig);
// }
//CTRL-/ (SIG_QUIT)
//per i children?serve?

void	*ft_handler(int sig)
{
	//pid_t child;
	//char	*new_prompt;

	//child = fork();
	if (sig == SIGINT)
	{
		(void)sig;
		write(1, "\n", 1);
		ft_suppress_output();

		rl_on_new_line();
		rl_redisplay();;
	}
	if (sig == SIGQUIT)
	{
		(void)sig;
		// waitpid(- 1, NULL, WUNTRACED);
		readline(ft_strjoin_free(PROMPT, "exit", 0, 0));
		rl_redisplay();
//			write(0, "exit", 5);
		//rl_replace_line("exit\n", 0);
		// waitpid(child, NULL, WUNTRACED);
		// if (child == fork())
		// {
		// 	rl_line_buffer = ft_strjoin(PROMPT, "exit\n");
		// 	readline(rl_line_buffer);
		//rl_redisplay();

		// }
		exit(3);
	}
	// if (sig == SIGTERM)
	exit(1);
}
//QUALCUNO PENSI AI BAMBINI!!!!(cit.)
