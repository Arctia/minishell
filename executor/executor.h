#ifndef EXECUTOR_H
# define EXECUOTIR_H

#include "../global.h"

/*
	***********************************************************
					ft_execve
	***********************************************************
*/

char	*ft_append(char * path, t_hellmini *shell);
char	**ft_getpath(t_hellmini *shell);
char	*ft_findpath(t_hellmini *shell, int i);
char	**ft_listtomatrix(t_command *cmd, t_hellmini *shell);

/*
	***********************************************************
					ft_pipe
	***********************************************************
*/
void	ft_pipe(t_hellmini *shell);
void	ft_pipeone(t_hellmini *shell);
void	ft_fixstinpipe(t_hellmini *shell, Pipe output);
void	ft_execvepipe(t_hellmini  *shell);

/*
	***********************************************************
					utils
	***********************************************************
*/

void	ft_freestrarr(char **split_arr);


#endif