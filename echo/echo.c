#include "./../global.h"

// int	ft_cmd(t_command *cmd)
// {
// 	printf("%s\n", cmd->args[1]);
// 	return (0);
// }
//
//Verifica come si comporta con i caratteri speciali tipo e accentata etc
//
int	str_add(char *str1, const char *str2)
{
	int	i;

	i = 0;
	while(str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (0);
}

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


// int	str_add(char *str1, const char *str2)
// {
// 	int	i;

// 	i = 0;
// 	while(str2[i])
// 	{
// 		str1[i] = str2[i];
// 		i++;
// 	}
// 	str1[i] = '\0';
// 	return (0);
// }

// int	put_str_fd(char *str, int fd)
// {
// 	int	i;

// 	i = 0;
// 	//str_add(str, str);
// 	while (str[i])
// 	{
// 		write (fd, &str[i], 1);
// 		i++;
// 	}
// 	return (i);
// }

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
	int	n;

	n = 0;
	while (n < argc - 1)
	{
		str_add(cmd->args[n], argv[n + 1]);
		n++;
	}
	return (0);
}

int	main(int argc,char **argv)
{
	t_command	*cmd;
	int			n_flag;
	int			n;
	int			to_ret;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	n_flag = 0;
	n = 1;
	to_ret = 0;
	echo_aux(argc, argv, cmd);
	if (!ft_strncmp(cmd->args[0], "echo", 4) && argc > 1)
	{
		if (!ft_strncmp(cmd->args[1], "-n", 3))
			n_flag = 1;
		while (n + n_flag < argc)
		{
			put_str_fd(cmd->args[n + n_flag], 1);
			n++;
			if (n + n_flag <= argc -2)
				write(1, " ", 2);
		}
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (to_ret);
}
