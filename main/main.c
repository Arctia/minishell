#include "../global.h"
#include "prompt_and_signals.h"
#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
# define PROMPT "\033[1;31mminisHELL$:\033[0m "

void	prompt_loop(t_hellmini *shell)
{
//signal
	//signal
	while(1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		shell->cmd->command = readline(PROMPT);

	}
}

int	main(int argc, char **argv, char **env)
{
	t_hellmini	shell;
	//env_init()
	(void)argc;
	(void)argv;
	(void)env;
	prompt_loop(&shell);

}
