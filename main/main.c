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
// void	here_doc_handler(char* str)
// {

// }
int	prompt_loop(t_hellmini *shell)
{
	// char *tmp_buf;

	// tmp_buf = ft_strdup("\033[1;31mminisHELL$:\033[0m exit\0");
	while(1)
	{

		signal(SIGINT, ft_sigs_handler);
		signal(SIGQUIT, SIG_IGN);
		//sigquit_macro(SIGQUIT, shell);
		shell->input = readline(PROMPT);
		if (!shell->input)
		{
			{
			//ft_suppress_output();
			//printf("\033[1;31mminisHELL$:\033[0m exit");
			//il write subito sotto MEZZO funziona
			//write(1,"\033[1;31mminisHELL$:\033[0m exit\0", 29);

			write(1, "\033[0;12Cexit", 12);
			//ft_putstr_fd("\033[0;12f exit", STDOUT_FILENO);
			//rl_line_buffer[0] = '\0';
			// write(1, "");
			//ft_putstr_fd("exit \033[11K\r", 11);
			//ft_putstr_fd("\033[0K\r exit", STDOUT_FILENO);
			//write(1, "\u001b[2K" , 0);
			//rl_replace_line("exit", 5);
			rl_redisplay();
			}
			exit(0);
		}
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);
	}

	//rip_and_tear(shell->current_cmd, shell->current_cmd->command);
	return (0);
}
// int	prompt_loop(t_hellmini *shell)
// {
// //signal
// 	while(1)
// 	{
// 		// signal(SIGINT, sigint_handler);
// 		// signal(SIGQUIT, sigquit_handler);
// 		signal(SIGINT, ft_sigs_handler);
// 		signal(SIGQUIT, ft_sigs_handler);
// 		//sigquit_macro(SIGQUIT, shell);
// 		shell->input = readline(PROMPT);
// 		if (!shell->input)
// 		{
// 			// rl_replace_line("\033[1;31mminisHELL$:\033[0m exit\n", 0);
// 			// shell->input = ft_strdup("exit");

// 			// rl_redisplay();
// 			// printf("\033[1;31mminisHELL$:\033[0m exit\n");
// 			rl_replace_line("exit", 0);
// 			//rl_redisplay();
// 			//write(1, "exit", 4);
// 			exit(0);
// 		}
// //			return (0 * write(1, "exit\n", 5));
// 		if (ft_strncmp(shell->input, "", 1))
// 			add_history(shell->input);

// 		//command_init(&shell);
// 		// if (!ft_strncmp(shell->input, "exit\n", 5))
// 		// {
// 		// 	//ft_free_structs();
// 		// 	exit(0);
// 		// }
// 	//	exp_tkn("$user", shell->env);
// 	}

// 	//rip_and_tear(shell->current_cmd, shell->current_cmd->command);
// 	return (0);
// }

void	init_shell(t_hellmini *shell)
{
	//shell->env = env
	//ft_putstr_fd("YO MAN", 1);
	init_shell_env(shell->env, *shell);
	shell->exit_status = 0;
	shell->input = NULL;
	shell->mc_pipes = 0;
	shell->mc_quotes = 0;
	shell->mc_wquotes = 0;
	shell->current_cmd = NULL;
	//shell->pid = 0;
	//printf("Shell initialized\n");
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
	//ft_putstr_fd(exp_tkn("USER", shell.env), 1);
	prompt_loop(&shell);

}
