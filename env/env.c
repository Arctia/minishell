#include "../global.h"

typedef struct s_dict
{
	char	*key;
	char	*value;
	void	*next;
}	t_dict;

typedef struct s_hellmini
{
	char **env;
	t_command *cmd; // we need it?


}           t_hellmini;

/*
	in main , parser o fill command :
	t_hellmini *minishell;
	shell.env = ft_ardup(envp);

	need libft 
	ft_putendl_fd()
	ft_putstr_fd();
	ft_putchar_fd();


	void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

*/

/*____________
LIBFT
______________*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}


/*____________
UTILS
______________*/


char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

int env(t_hellmini *minishell)
{
	// t_hellmini *minishell; //
	int	i;

	i = 0;
	while (minishell->env)
	{
		ft_putendl_fd(minishell->env[i], 1);
		i++;

	}
	return (0);
}

int main(char **envp)
{
	t_hellmini	*minishell;

	minishell->env = ft_arrdup(envp);


	return  (env(&minishell));


}