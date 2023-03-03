#include "executor.h"

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

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	path == usr/bin/ls
	arg == bin/ls			-la
	arg is a matrix with:
*/

ft_execv(t_hellmini  *shell)
{
	char * path;
	char **arg; //array[4] tt a null e metto dentro i cmd che mi servono
	char **env;

	arg = ft_listtomatrix();
	path = ft_findpath(shell);
	 if (execve(path,arg,env) == -1) {
      perror("execution failed");
    }
    exit(EXIT_FAILURE);
	
}

// Bultin ?
// No built in ?````
//     Fork
//     Find path -> execv

/*
	***********************************************************
					FT_EXECUTOR					
	***********************************************************
	is pseudocode (i commenti sparsi nel codice sono temporanei
	man mano che completo il codice li levo)

	== should be a strcmp

	maybe i need fd_in and fd_out in the command struct to swap 
	fd between pipe

	maybe wrong use of perror
*/
ft_executor(t_hellmini *parser)
{
	int		fd[2];
	int		pid;
	int		fd_in;

	fd_in = STDIN_FILENO;

	while (parser->current_command)
	{
		if (parser->flag == 1)
			ft_expander();
		if (parser->cmd->operator == NULL)
		{
			if(parser->current_command == builtin)
				ft_builtin();
			else
				ft_execve();
		}
		//pipe(fd);
		else if (parser->current_command == '<<')
			ft_heredoc();
		else if (parser->current_command == '>')
			ft_redir();
		else if (parser->current_command == '|')
		{
			pid = fork(); //maybe in directly in ft_execv?
			if (pid == 0)
				ft_execv(parser->current_command);
			else if ( pid < 0)
				perror("fork failed");
			// else
			// {
			// 	waitpid(pid, &status, WUNTRACED);
			// 	while (!WIFEXITED(status) && !WIFSIGNALED(status))
			// 	waitpid(pid, &status, WUNTRACED);
			// }

			// fd_in fd_out
			fd1 = dup(fd0);	//clone fd
			close(fd0);
			dup2(fd3,fd4);	//clone fd3 on fd4 
			close(fd3);//dup2 duplicate the fd so is good to close the old one
		}
		if(parser->cmd->next)
			parser->current_command =parser->cmd->next;
		
	}
}