#include "./../global.h"

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

int	ft_strlen(char *str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
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
	n = 0;
	to_ret = 0;
	echo_aux(argc, argv, cmd);
	if (!ft_strncmp(cmd->args[0], "echo", 4) && argc > 1)
	{
		while (!ft_strncmp(cmd->args[++n], "-n", 3))
			n_flag = 1;
		while (n < argc)
		{
			put_str_fd(cmd->args[n++], 1);
			if (n <= argc -2)
				write(1, " ", 1);
		}
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (to_ret);
}

//Penso che nel .h convenga distinguere una struct shell ed una la struct command.
//in modo che la shell abbia le sue variabili(come l'env, le built-in, la history dei comandi)
//e la history/ array degli exit-status dei comandi) ed i singoli comandi vadano ad interagire
// con la shell.(in questo modo oltre a visualizzare meglio il codice risparmiamo anche righe
//in termini di norma, piccolissimo dettaglio da non sottovalutare per ridurre leggermente
//il numero di bestemmie).
//Una volta impostato il .h in questo modo, con sia il parser che il lexer/tokenizer
//funzionanti, il comando echo dovrebbe apparire simile a quello che segue,
//con t_command = t_shell curr_cmd:
//
//int	echo(int n_words,char **words, t_command *cmd)
//{
//		int			n_flag;
//		int			n;
//
//		shell->to_ret = 0;
//		cmd = (t_command *)malloc(sizeof(t_command));
//		if (!cmd)
//			shell->to_ret = 0;
//		n_flag = 0;
//		n = 0;
//		echo_aux(argc, argv, cmd);
//		while (!ft_strncmp(cmd->args[++n], "-n", 3))
//			n_flag = 1;
//		while (n < argc)
//		{
//			put_str_fd(cmd->args[n++], 1);
//			if (n <= argc -2)
//				write(1, " ", 1);
//		}
//		if (!n_flag)
//			write(1, "\n", 1);
//		return (shell->to_ret);
//}
