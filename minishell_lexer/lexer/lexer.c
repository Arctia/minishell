#include "global.h"

int	check_argument(char *line, int i, char chr) //second part and actual working function of "check_closure" below
{
	int	flag;

	flag = 1;
	while (line[i] != 0 || line[i] != chr)
	{
		if ((line[i] == '\"' || line[i] == '\'') && line[i] != chr)
			flag *= -1;
		i++;
	}
	if (line[i] == 0 || flag != -1)
		return (-1);
	return (i);
}

int check_closures(char *line, int i, t_command *com) //makes sure no quotes are weirdly innested into each other, redirecting to "check argument"
{
	int	quotes;

	quotes = 1;
	while (line[i] != 0)
	{
		if (line[i] == '\"')
		{
			i = check_argument(line, i + 1, '\"');
			if (i == -1)
				return (-1);

		}
		else if (line[i] == '\'')
		{
			i = check_argument(line, i + 1, '\'');
			if (i == -1)
				return(-1);
		}
		i++;
	}
}

int	check_quotes(char *line, int i, t_command *com) //makes sure to ignore any operator inside quotes.
{
	char	*quote;

	quote == line[i];
	while (line[i++] != quote)
	{
		if (quote == '\"' && line[i] == '$')
			com->exp = 1;
		i++;
	}
	return (i);
}

int	lexer(char *line, t_command *com) //searches and split following commands from the line on the next command argument
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '\"' || line[i] == '\'')
		i = check_quotes(line, i, com);
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			com->next = (t_command*)malloc(sizeof(t_command));
			if (!com->next)
				return (-1);
			com->command = (char *)malloc(sizeof(split_operator(line)));
			com->next->command = split_operator(line);
			line = split_line(line);
			i = 0;
		}
	}
	return (0);
}

char	lexer_start(char *line, t_command *com) //starts splitting the first command from the line on the current command argument of the struct.
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (line[i] != 0 || flag != 1)
	{
		if (line[i] == '\"' || line[i] == '\'')
		i = check_quotes(line, i, com);
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			com->current_cmd = (t_command*)malloc(sizeof(t_command));
			if (!com->current_cmd)
				break ;
			
			com->current_cmd = split_operator(line);
			line = split_line(line);
			flag = 1;
		}
	}
	return (line);
}

int lexer_init(t_hellmini *shell) //main function and of the lexer process, it initializes the struct, checks unclosed quotes.
{
	char		*line
	int			i;
	t_command	*com;

	line = shell->input;
	i = 0;
	shell->com = (t_command*)malloc(sizeof(t_command));
	if (!com)
		return (-1);
	if (check_closures(line, i, com) != 0)
	{
		lexer_error("unclosed quotes.", com);
		return (-1);
	}
	line = lexer_start(line, com);
	if (lexer(line, com) != 0)
		return (-1);
	free(line);
	return (0);
}

int main(int argc, char **argv)		//testing main, remove after testing
{
	lexer_init(argv[1]);
	return (0);
}