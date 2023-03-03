#include "executor.h"

char    **ft_listtomatrixx(t_hellmini)
{
    
}

/*
	***********************************************************
                    FT_APPEND
	***********************************************************
    working
*/

char	*ft_append(char * path, t_hellmini *shell)
{
	char	*ret;
	int		i;

	i = -1;
	ret = malloc(sizeof(char *) * (ft_strlen(path) + ft_strlen(shell->current_command)) + 1);
	if (!ret)
		return NULL;
	while (*path)
		*ret++ = *path++;
	while (*shell->current_command++)
		*ret++ = *shell->current_command++;
	*ret++ = '\0';
	return (ret);
	// ret = ft_strdup(path);
}

/*
	***********************************************************
					FT_GETPATH
	***********************************************************
	working
    path da freeare
*/

char	**ft_getpath(t_hellmini *shell)
{
	int		i;
	char	**path;

	i = 0;
	while (shell->env[i])
	{
		if(ft_strncmp("PATH" ,shell->env[i], 4) == 0)
		{
			path = ft_split(ft_strtrim(shell->env[i], "PATH="), ':');
			break;
		}
		i++;
	}
	return (path);		
}

/*
	***********************************************************
					FT_FINDPATH
	***********************************************************
	working
*/

char	*ft_findpath(t_hellmini *shell)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**path;
	int				i;

	i = 0;
	path = ft_getpath(shell); //path alloca probabilemnte devo allocare per usare strtrim e freeare
	while (path[i])
	{
		dir = opendir(path[i]);
        if (!dir)
            return (NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strcmp(entry->d_name,shell->current_command))
			{
				closedir(dir);
				return(ft_append(path[i], shell));
			}
			entry = readdir(dir);
		}
		closedir(dir);
		i++;
	}
	return (NULL);
}