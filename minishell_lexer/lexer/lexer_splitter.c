#include "global.h"

void	lexer_error(char *message) //example and sketch of an exit error function, not really integrated with the minishell
{
	printf("Error: %s\n", message);
	//free(com->shell->input);
	//free(com);
}

int	split_operator_line(char *line, int i) //looks for the index where to split the line between command and line yet to be checked.
{
	char	quote;
	char	operator;
	
	while (line[i] != 0)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			i++;
			quote == line[i];
			while (line[i] != quote)
				i++;
		}
		if (line[i] == '|')
			break ;
		else if (line[i] == '<' || line[i] == '>')
		{
			operator = line[i];
			if (line[i + 1] == operator)
				i++;
			break;
		}
		i++;
	}
	return (i);
}

//splits the line with the following command from the line yet to be checked
char	*split_operator(char *line, int *ff)
{
	static int	r;
	char		*ret;
	int			i;
	int			j;

	if (!r)
		r = 0;
	j = 0;
	i = split_operator_line(line, *ff);
	ret = (char *) malloc(sizeof(char) * i + 1);
	while (j <= i)
	{
		ret[j] = line[j + r];
		j++;
	}
	ret[j] = '\0';
	*ff = i;
	r = j;
	return (ret);
}

//splits the line yet to be controlled from the command already split
char	*split_line(char *line)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	//i = split_operator_line(line);
	i = 0;
	while (line[i] != 0)
	{
		ret[j] = line[i];
		j++;
		i++;
	}
	return (ret);
}
