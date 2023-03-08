#ifndef EXECUTOR_H
# define EXECUOTIR_H

#include "../global.h"

typedef int	Pipe[2];
/*
	***********************************************************
					execv.c
	***********************************************************
*/
char	*ft_append(char * path, t_hellmini *shell);
char	**ft_getpath(t_hellmini *shell);
char	*ft_findpath(t_hellmini *shell, int i);
char	**ft_listtomatrix(t_hellmini *shell);
/*
	***********************************************************
					pipe.c
	***********************************************************
*/
void	ft_pipe(t_hellmini *shell);
void	ft_pipejunior(t_hellmini *shell);
void	ft_fixstinpipe(t_hellmini *shell, Pipe output);
void	ft_execvepipe(t_hellmini *shell);
/*
	***********************************************************
					redir.c
	***********************************************************
*/
char	*ft_name();
void	ft_less(t_hellmini *shell);												//	<
void	ft_redirection(t_hellmini *shell);										//	>
void	ft_moremore(t_hellmini *shell); // lo so è sbajato ma fa piu' ride		//	>>
void	ft_heredoc(t_hellmini *shell);											//	<<
/*
	***********************************************************
					utils
	***********************************************************
*/
void	ft_freestrarr(char **split_arr);


#endif