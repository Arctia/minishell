#include "executor.h"

/*
	***********************************************************
					FT_LISTTOMATRIX
	***********************************************************
	working
	arg is allocated remember to free
	there is both t_command both t_hellmini perchè pe testa non 
	know how to do
*/

char	**ft_listtomatrix(t_command *cmd, t_hellmini *shell)
{
	char	**arg;
	int		i;
	int		j;

	arg = NULL;
	i = 1;
	j = 0;
	while (cmd->arguments[j++])
		i++;
	j = 0;
	while (cmd->flags[j++])
		i++;
	arg = ft_calloc(sizeof(char *), i);
	arg[0] = ft_strdup(shell->current_command);
	i = 1; 
	j =	-1;
	while (cmd->flags[++j])
		arg[i++] = ft_strdup(cmd->flags[j]);
	j = -1;
	while (cmd->arguments[++j])
		arg[i++] = ft_strdup(cmd->arguments[j]);
	arg[i++] = NULL;
	return (arg);
}

/*
	***********************************************************
					FT_APPEND
	***********************************************************
	working
	ret is allocated remember to free
*/

char	*ft_append(char *path, t_hellmini *shell)
{
	char	*ret;
	char	*retaux;

	ret = malloc(sizeof(char ) * (ft_strlen(path) + 
			ft_strlen(shell->current_command)) + 2);
	if (!ret)
		return (NULL);
	retaux = ret;
	while (*path)
		*ret++ = *path++;
	*ret++ = '/';
	while (*shell->current_command)
		*ret++ = *shell->current_command++;
	*ret++ = '\0';
	return (retaux);
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
	char	*temp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("PATH", shell->env[i], 4) == 0)
		{
			temp = ft_strtrim(shell->env[i], "PATH=");
			path = ft_split(temp, ':');
			free(temp);
			break ;
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
	la i passata è una porcata ma su due piedi era la cosa piu''
	facile per essere a norma e non avere leak
*/

char	*ft_findpath(t_hellmini *shell, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**path;
	char			*temp;
	// int				i;

	i = 0;
	path = ft_getpath(shell);
	while (path[i])
	{
		dir = opendir(path[i]);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strcmp(entry->d_name, shell->current_command))
			{
				closedir(dir);
				temp = ft_append(path[i], shell);
				ft_freestrarr(path);
				return (temp);
			}
				entry = readdir(dir);
		}
		closedir(dir);
		i++;
	}
	return (NULL);
}
