#include "global.h"

/*
	***********************************************************
					FT_EXPANDER
	***********************************************************
	Before a node from t_simple_cmds is handled it is expanded.
	The expander takes variables, identified by $,
	and replaces them with their value from 
	the environment variables. Such that $USER becomes mgraaf,
	and $? is replaced with the exit code.

	Pay attention to export : export a = ls
	$a-> ls
*/
ft_expander()
{

}

// Bultin ?
// No built in ?````
//     Fork
//     Find path -> execv

/*
	***********************************************************
					FT_EXECUTOR					
	***********************************************************
	is pseudocode
*/
ft_executor(t_command *parser)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (loop on t_command node from parser)
	{
		if (parser->command == '$')
			ft_expander();
		if (parser->command == '<<')
			ft_heredoc();
		if (parser->command == builtin[i])
			builtin[i];					//ft_builtin
		else
		{
			pid = fork(); //maybe in ft_fork or ft_simplecommand

			


			ft_simple_command(parser->command);
		}
		
	}
}