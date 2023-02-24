#include "./../global.h"

// int	ft_cmd(t_command *cmd)
// {
// 	printf("%s\n", cmd->args[1]);
// 	return (0);
// }
//
//ALLO STATO ATTUALE NON COPIA argv nella matrice args(o quanto minimo li stampa vuoti),
// inizializzati male o non terminati?

int	put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}
int	str_add(char *str1, const char *str2)
{
	int	i;

	i = 0;
	while(str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	//str1[i] = '\0';
	//printf("%s\n", str1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	while (*s1 != '\0' && *s2 != '\0' && n > 0)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	echo_aux(int argc, char **argv, t_command *cmd)
{
	//int	i;
	int	n;
	//t_command	*tmp;
	//tmp = cmd;

	//i = 0;
	n = 0;
	while(n < argc - 1)
	{
		str_add(cmd->args[n], argv[n + 1]);
		//put_str_fd(&cmd->args[0][n], 1);
		//write(1, "dioporco\n", 10);
		//printf("%d\n", n);
		//printf("%ld\n", strlen(cmd->args[n]));
		n++;
	}
	//str_add(&cmd->args[0][n], "\0");
	//printf("%ld\n", strlen(&cmd->args[0][n]));
	return (0);
}

int	main(int argc,char **argv)
{
	t_command	*cmd;
	int			i;
	int			n;
	int			to_ret;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	i = 0;
	n = 0;
	to_ret = 0;
	echo_aux(argc, argv, cmd);
	if (!ft_strncmp(cmd->args[0], "echo", 4) && argc > 1)
	{
		if (!ft_strncmp(cmd->args[1], "-n", 3))
		{
			put_str_fd(cmd->args[2], 1);
			write(1, "\%", 2);
			to_ret = 0;
		}
		else
		{
			put_str_fd(cmd->args[1], 1);
			write(1, "\n", 1);
		}
	}
	if (argc == 1)
		write(1, "\n", 1);
	return (to_ret);
}
