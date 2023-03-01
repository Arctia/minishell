#include "../global.h"

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
					FT_GETPATH
	***********************************************************


*/

char	*ft_getpath(t_hellmini *shell)
{
	while (shell->env[i++])
		while (shel.env[j++])
	;
}

//
char	*ft_findpath()
{
	DIR				dir;
	struct dirent	*entry;//studia!!
	while()
	{
		opendir;
		readdir;
		closedir;
	}
	split($,:);
	return (path);
}

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	path == usr/bin/ls
	arg == bin/ls			-la
	arg is a matrix with:
	in n "cmd name" in n+1 "eventually opt(flag)" in n+2 "argument"
*/

ft_execv()
{
	char * path;
	char **arg; //array[4] tt a null e metto dentro i cmd che mi servono
	char **env;

	arg = ft_listtomatrix();
	path = ft_findpath();
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

		if (parser->flag == '$')
			ft_expander();
		pipe(fd);
		if (parser->command == '<<')
			ft_heredoc();
		else if (parser->command == builtin[i])
			builtin[i];		//array con selettore funzioni
		else if (parser->command == '|')
		{
			pid = fork(); //maybe in directly in ft_execv?
			if (pid == 0)
				ft_execv(parser->command);
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
		else
		{
			ft_execv(parser->command);
		}
		if(parser->current_command.next)
			parser->current_command =parser->current_command.next;
		
	}
}