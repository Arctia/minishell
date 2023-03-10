#include "global.h"


int	ft_strlen(char *str)
{
	int i = 0;

	while(str[i])
		str[i++];
	return (i);
}

//second part and actual working function of "check_closure" below
int	check_argument(char *line, int i, char chr)
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

//makes sure no quotes are weirdly innested into each other, redirecting to "check argument"
int check_closures(char *line, int i)
{
	int	quotes;
	char	q;

	quotes = 1;
	while (line[i] != 0)
	{
		q = line[i];
		// maybe need a rewrite


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

//makes sure to ignore any operator inside quotes.
int	check_quotes(char *line, int i, t_command *com) 
{
	char	quote;

	quote = line[i];
	while (line[i++] != quote)
	{
		if (quote == '\"' && line[i] == '$')
			com->spc[CASH] = 1;
		i++;
	}
	return (i);
}

//searches and split following commands from the line on the next command argument
void	lexer_default(char *line, t_command *cmd)
{
	t_command *tmp;
	int	i;

	i = 0;
	while (1)
	{
		if (cmd == NULL)
		{
			cmd = (t_command *) malloc(sizeof(t_command));
			if (!cmd)
				return ;
			cmd->next = NULL;
			tmp->next = cmd;
			cmd->prev = tmp;
		}
		if (line[i] == 0 || line[i] == '|' || line[i] == '<' || line[i] == '>')
		{	
			cmd->str = split_operator(line, &i);
			tmp = cmd;
			cmd = cmd->next;
		}
		if (line[i] == '\0')
			break ;
		i++;
	}
}

void	print_commands(t_command *cmd)
{
	t_command *tmp;

	tmp = cmd;

	while (tmp != NULL && tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

//main function and of the lexer process, it initializes the struct, checks unclosed quotes.
int lexer_init(t_hellmini *shell)
{
	char		*line;
	int			i;

	line = shell->input;
	i = 0;
	if (check_closures(line, i) != 0)
	{
		lexer_error("unclosed quotes.");
		return (-1);
	}
	shell->current_cmd = (t_command *)malloc(sizeof(t_command));
	if (!(shell->current_cmd))
		return (-1);
	lexer_default(line, shell->current_cmd);
	print_commands(shell->current_cmd);
	return (0);
}


//testing main, remove after testing
int main(int argc, char **argv)
{
	t_hellmini shell;
	int	i;

	shell.input = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	while (i < ft_strlen(argv[1]))
	{
		shell.input[i] = argv[1][i];
		i++;
	}
	shell.input[i] = '\0';

	lexer_init(&shell);
	
	return (0);
}
