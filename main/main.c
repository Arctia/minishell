#include "../global.h"
#include "prompt_and_signals.h"
#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
# define PROMPT "\033[1;31mminisHELL$:\033[0m "

//rip_and_tear is the name of a song from DOOM's O.S.T..
//I think it's quite an appropriate name for the process of splitting and
//tokenizing the input. And it's quite some badass music.
//If you don't agree, feel free to go and f##k off :)


// int	command_init(t_command command)
// {

// }
int	prompt_loop(t_hellmini *shell)
{
//signal
	//signal
	while(1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		shell->input = readline(PROMPT);
		if(!shell->input)
			return (0 * write(1, "\n", 1));
		//command_init(*shell->current_cmd);
		if (ft_strncmp(shell->input, "exit", 4))
			exit(0);
	}
	rip_and_tear(shell->current_cmd, shell->current_cmd->command);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_hellmini	shell;
	//env_init()
	//shell_init?
	(void)argc;
	(void)argv;
	(void)env;
	prompt_loop(&shell);

}
