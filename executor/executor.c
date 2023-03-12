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

	"" '' are alredy gestite from lexer/parser?
*/

char	*ft_expander(char *str, char **env)
{
	int i;
	int j;
	int k;
	char    *new_token;
	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (!((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	while(env[i][j] != '=')
		j++;
	j++;
	new_token = (char *)malloc((ft_strlen(env[i]) + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while (env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}

/*
	***********************************************************
					FT_BUILTIN
	***********************************************************
	is not mine, is magic from madrid should be ok
	prototype:
	int	ft_namebultin(t_hellmini *shell)

int	(*ft_builtin(char *str))(t_hellmini *shell)
{
	static void	*builtins[7][2] = {
	{"echo", ft_echo},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"unset", ft_unset},
	{"env", ft_env},
	{"exit", ft_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}*/

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	working 
	l'ultimo else mi è un po' oscuro 
	we have to decide if do the fork in ft execve or in executor
*/

void	ft_execv(t_hellmini *shell, pid_t pid)
{
	char	*path;
	char	**arg; /* array[4] tt a null e metto dentro i cmd che mi servono */
	//char	**env;
	int		status;

	arg = ft_listtomatrix(shell);
	path = ft_findpath(shell, 0);
	pid = fork();
	if (!pid)
	{
		if (execve(path, arg, shell->env) == -1)
			perror("execv execution failed");
	}
	else if (pid < 0)
		perror("execv fork failed");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	ft_free_cmatrix(arg);
	free(path);
	// exit(EXIT_FAILURE);
}

/*
	***********************************************************
					FT_EXECUTOR					
	***********************************************************
	the name is parser because it come from Parser
	
	i've to find the rgiht way to execute all command my if is
	good only for simple command
	

	maybe i need fd_in and fd_out in the command struct to swap 
	fd between pipe or maybe not

*/
void	ft_executor(t_hellmini *parser)
{
	pid_t	pid;

	//int		status;
	pid = 111;
	while (parser->current_cmd)
	{
		if (parser->current_cmd->spc[DQUOTE] || parser->current_cmd->spc[CASH])
			parser->current_cmd->command
				= ft_expander(parser->current_cmd->command, parser->env);
		if (parser->current_cmd->next == NULL)	//simple command?
		{
			// if (ft_strcmp(parser->current_cmd->command, builtin[i]))
			//if (ft_builtin(parser->current_cmd->command))
			//	;
			//else
			ft_execv(parser, pid);
		}
		else if (parser->current_cmd->spc[REDIN])
			ft_less(parser);
		else if (parser->current_cmd->spc[REDOUT])
			ft_redir(parser);
		else if (parser->current_cmd->spc[REDAPP])
			ft_moremore(parser);
		else if (parser->current_cmd->spc[HERDOC])
			ft_heredoc(parser);
		else if (parser->current_cmd->spc[PIPE])
		{
			ft_pipe(parser);
			// while (waitpid(0, &status ,0))
			// 	;//? not sure if here or in ft_executor with a while loop
		}
		// ft_execv(parser, pid); //see function comment maybe every single exceptio call his own ft_sexecv
		// if (parser->current_cmd->next)
			parser->current_cmd = parser->current_cmd->next;
	}
}
