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
char	*ft_findpath(t_hellmini *shell);

#endif