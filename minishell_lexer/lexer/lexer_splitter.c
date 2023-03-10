#include "global.h"

void	lexer_error(char *message, t_command *com) //example and sketch of an exit error function, not really integrated with the minishell
{
	printf("Error: %s\n", message);
	free(com->shell->input);
	free(com);
}

int	split_operator_line(char *line) //looks for the index where to split the line between command and line yet to be checked.
{
	char	quote;
	char	operator;
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote == line[i];
			while (line[i++] != quote)
				i++;
		}
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			operator = line[i];
			while (line[i + 1 ] == operator)
				i++;
			break;
		}
		i++;
	}
	return (i);
}

char	*split_operator(char *line) //splits the line with the following command from the line yet to be checked
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = split_operator_line(line);
	while (j <= i)
	{
		ret[j] = line[j];
		j++;
	}
	return (ret);
}

char	*split_line(char *line) //splits the line yet to be controlled from the command already split
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	i = split_operator_line(line);
	while (line[i] != 0)
	{
		ret[j] = line[i];
		j++;
		i++;
	}
	return (ret);
}