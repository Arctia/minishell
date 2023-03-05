#include "../global.h"
#include "prompt_and_signals.h"
#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
//# define PROMPT "\033[1;31mminisHELL$:\033[0m "

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
	while(1)
	{
		signal(SIGINT, sigint_handler);
		//signal(SIGQUIT, sigquit_handler);
		sigquit_macro(SIGQUIT, shell);
		shell->input = readline(PROMPT);
		if (!shell->input)
			return (0 * write(1, "exit\n", 5));
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);

		//command_init(&shell);
		if (!ft_strncmp(shell->input, "exit\n", 5))
		{
			//ft_free_structs();
			exit(0);
		}
		// exp_tkn("$user", shell->env);
	}

	//rip_and_tear(shell->current_cmd, shell->current_cmd->command);
	return (0);
}

void	init_shell(t_hellmini *shell)
{
	//shell->env = env
	ft_putstr_fd("YO MAN", 1);
	init_shell_env(shell->env, *shell);
	shell->exit_status = 0;
	shell->input = NULL;
	shell->mc_pipes = 0;
	shell->mc_quotes = 0;
	shell->mc_wquotes = 0;
	shell->current_cmd = NULL;
	//shell->pid = 0;
	printf("Shell initialized\n");
}

int	main(int argc, char **argv, char **env)
{
	t_hellmini	shell;

	//shell_init?
	(void)argc;
	(void)argv;
	shell.env = env;
	init_shell_env(shell.env, shell);
	init_shell(&shell);
	prompt_loop(&shell);

}
