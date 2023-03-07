#include "executor.h"

typedef int	Pipe[2];

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
	different ft_execv without fork i don't know if needed
*/

void	ft_execvepipe(t_hellmini  *shell)
{
	char	*path;
	char	**arg; //array[4] tt a null e metto dentro i cmd che mi servono
	char	**env;

	arg = ft_listtomatrix(shell->cmd, shell);
	path = ft_findpath(shell, 0);
	if (execve(path,arg,env) == -1) 
		perror("execution failed");
	ft_freestrarr(arg);
	free(path);
	// exit(EXIT_FAILURE);
}

/*
	***********************************************************
					ft_fixstinpipe
	***********************************************************
	dealt with the in and out of command and recall ft pipejunior 
	for eventually other pipe 
*/

void	ft_fixstinpipe(t_hellmini *shell, Pipe output)
{
	dup2(output[1], 1);
	close(output[0]);
	close(output[1]);
	if (shell->cmd->next->operator == NULL)
		return ;
	ft_pipejunior(shell);

}

/*
	***********************************************************
					ft_pipejunior
	***********************************************************
	pipe fork chek
	maybe ft_execpipe must be bring here
*/

void	ft_pipejunior(t_hellmini *shell)
{
	pid_t	pid;
	Pipe	input;

	if (shell->cmd->operator == '|')
	{
		if(pipe(input) != 0)
			perror("failed to create pipe");
		if ((pid = fork() < 0))
			perror("failed to fork");
		if (!pid)
			ft_fixstinpipe(shell, input);
		dup2(input[0], 0);
		close(input[0]);
		close(input[1]);
	}
	ft_execvepipe(shell);
}

/*
	***********************************************************
					ft_pipe
	***********************************************************
	making start the magic trick 
	maybe ft_execpipe must be bring in an other function
	i've to study the  if else state to break the while 
*/

void	ft_pipe(t_hellmini *shell)
{
	pid_t	pid;
	int		status;


	while (shell->cmd->operator == '|')
	{
		if ((pid = fork()) < 0)
			perror("failed to fork");
		if (pid != 0)
			return ; //  wait??
		ft_pipejunior(shell->current_command);
		if (shell->cmd->next->operator=='|')
			shell->current_command = shell->cmd->next->command;
		waitpid(0, &status ,0);//? not sure if here or in ft_executor with a while loop
	}

}
