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
char	*ft_expander(char *str, char **env)
{
	int	i;
	int	j;
	int	k;
	char	*new_token;
	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (ft_strncmp(str, env[i], ft_strlen(str)))
		i++;
	while (env[i][j] != '=')
		j++;
	new_token = (char *)malloc(ft_strlen(env[i] + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while(env[i])
	{
		new_token[k++] = env[i][j++];
		//write for debug only
		//write(1, &new_token[k], 1);
	}
	new_token[k] = '\0';
	return (new_token);
}

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	working 
	l'ultimo else mi è un po' oscuro 
	we have to decide if do the fork in ft execve or in executor
*/

void	ft_execv(t_hellmini  *shell, pid_t pid)
{
	char	*path;
	char	**arg; //array[4] tt a null e metto dentro i cmd che mi servono
	char	**env;
	int		status;

	arg = ft_listtomatrix(shell->cmd, shell);
	path = ft_findpath(shell, 0);
	pid = fork();
	if (!pid)
	{
		if (execve(path,arg,env) == -1) 
			perror("execution failed");
	}
	else if (pid < 0)
			perror("fork failed");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	ft_freestrarr(arg);
	free(path);
	// exit(EXIT_FAILURE);
}

// Bultin ?
// No built in ?````
//     Fork
//     Find path -> execv

/*
	***********************************************************
					FT_EXECUTOR					
	***********************************************************
	the name is parser because it come from Parser
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
	pid_t	pid;
	int		fd_in;

	fd_in = STDIN_FILENO;

	while (parser->current_command)
	{
		if (parser->cmd->export == 1)
			ft_expander(parser->current_command, parser->env);
		if (parser->cmd->operator == NULL)
		{
			if(parser->current_command == builtin[])
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
			ft_pipe()
			// pipe(fd);
			// close(fd[0]);
			// if (parser->cmd->next == NULL)
			// 	dup2(fd[1],STDOUT_FILENO);
			// 	ft_execv(parser->current_command,pid);

			// // fd_in fd_out
			// fd1 = dup(fd0);	//clone fd
			// close(fd0);
			// dup2(fd3,fd4);	//clone fd3 on fd4 
			// close(fd3);//dup2 duplicate the fd so is good to close the old one
		}
		if(parser->cmd->next)
			parser->current_command =parser->cmd->next;
		
	}
}