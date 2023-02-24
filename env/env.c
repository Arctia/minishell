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
	// if (s[0] == 0)
	// 	return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (i);
	while (str[i])
		i++;
	return (i);
}

void	*ft_bzero(void *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)str)[i] = '\0';
		i++;
	}
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	int		*ret;

	ret = malloc(count * size);
	if (!ret)
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s1);
	s2 = (char *)malloc((size * sizeof(char)) + 1);
	if (!s2)
		return (0);
	while (i < size)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
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
	rtn[i] = NULL;
	return (rtn);
}

int env(t_hellmini *minishell)
{
	// t_hellmini *minishell; //
	int	i;

	i = 0;
	while (minishell->env[i])
	{
		// if (minishell->env[1][0] == 0)
		// 	break ;
		ft_putendl_fd(minishell->env[i], 1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_hellmini	minishell;
	int a;

	minishell.env = ft_arrdup(envp);
	a = env(&minishell);
	return (0);
}