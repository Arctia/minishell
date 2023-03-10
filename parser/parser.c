
#include "../global.h"

/*##############################################################################
#	Help Functions
############################################################################*/

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	debug(char *str)
{
	static char count = '0';

	write(1, &count, 1);
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	count += 1;
}

int	ft_isspace(int c)
{
	if (9 <= c && c <= 13 || c == 32)
		return (1);
	return (0);
}

int	ft_isnotspace(int c)
{
	if (9 <= c && c <= 13 || c == 32)
		return (0);
	return (1);
}

int	until_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isnotspace(str[i]))
		i++;
	return (i);
}

void	move_to_next_char(t_command *cmd)
{
	while (cmd->str[0] && ft_isspace(cmd->str[0]))
		cmd->str++;
}

/*##############################################################################
#	Set command name
############################################################################*/
static void	set_command_name(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->command = (char *) malloc(sizeof(char)
			* ft_strlen(cmd->tokens[0]) + 1);
	while (cmd->tokens[0][i++])
		cmd->command[i - 1] = cmd->tokens[0][i - 1];
	cmd->command[i] = '\0';
}

static void	set_arguments(t_command *cmd, int args)
{
	int	i;
	int	j;

	cmd->arguments = (char **) malloc(sizeof(char *) * args);
	if (!(cmd->arguments))
		return ;
	i = 1;
	while (i < args)
	{
		cmd->arguments[i - 1] = (char *) malloc(sizeof(char)
				* ft_strlen(cmd->tokens[i]) + 1);
		if (cmd->arguments[i - 1])
		{
			free(cmd->arguments);
			return ;
		}
		j = 0;
		while (cmd->tokens[i][j++])
			cmd->arguments[i - 1][j - 1] = cmd->tokens[i][j - 1];
		cmd->arguments[i - 1][j] = '\0';
		i++;
	}
}

/*##############################################################################
#	Splitter Functions
############################################################################*/
/* __ items in string ___________________?______________________________________
		. return number of items to be stored
_________________________________________!_________________________________ */
int	items_in_string(char *str)
{
	int	items_number;
	int	in_word;
	int	i;

	i = 0;
	in_word = 0;
	items_number = 0;
	while (str[i])
	{
		if (ft_isnotspace(str[i]) && !in_word)
		{
			in_word = 1;
			items_number++;
		}
		else
			in_word = 0;
		i++;
	}
	return (items_number);
}

/* __ Replace string ____________________?______________________________________
		- cycle until space found
		- inner cycle for quote/s (do not consider inside different quote)
_________________________________________!_________________________________ */
void	write_word_expander(char *cnt, char *str)
{
	char	fchar;
	int		i;

	i = 0;
	fchar = str[0];
	while (ft_isnotspace(str[0]))
	{
		fchar = str[0];
		if ((fchar == '\'' || fchar == '\"') && str++[0])
		{
			while (str[0] && str[0] != fchar)
				cnt[i++] = str++[0];
		}
		else
			cnt[i++] = str++[0];
	}
	cnt[i] = '\0';
}

void	write_word(char *cnt, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[0] && ft_isnotspace(cmd->str[0]))
		cnt[i++] = cmd->str++[0];
	cnt[i] = '\0';
}

/* __ split string ______________________?______________________________________
		. Count items to be store and allocate them
		. Allocate every single item
		. Write them
_________________________________________!_________________________________ */
int	split_string(t_command *cmd)
{
	int	test = 0;
	char	*init;
	int		items;
	int		c;

	init = cmd->str;
	move_to_next_char(cmd);
	items = items_in_string(cmd->str);
	cmd->tokens = (char **) malloc(sizeof(char *) * items + 1);
	if (!(cmd->tokens))
		return (0);
	c = 0;
	while (cmd->str[0] != 0)
	{
		cmd->tokens[c] = (char *) malloc(sizeof(char)
				* until_space(cmd->str) + 1);
		if (!(cmd->tokens[c]))
			return (0);
		write_word(cmd->tokens[c], cmd);
		move_to_next_char(cmd);
		c++;
	}
	cmd->tokens[c] = NULL;
	cmd->str = init;
	return (items);
}

void	init_flags(t_command *cmd)
{
	int	i;

	i = 7;
	while (i >= 0)
		cmd->spc[i--] = 0;
}

void	set_cmd_flags(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[i])
	{
		if (cmd->str[i] == '|')
			cmd->spc[PIPE] = 1;
		else if (cmd->str[i] == '\'' && cmd->spc[DQUOTE] == 1)
			cmd->spc[MQUOTE] = 1;
		else if (cmd->str[i] == '"' && cmd->spc[SQUOTE] == 1)
			cmd->spc[MQUOTE] = 1;
		else if (cmd->str[i] == '\'')
			cmd->spc[SQUOTE] = 1;
		else if (cmd->str[i] == '"')
			cmd->spc[DQUOTE] = 1;
		else if (cmd->str[i] == '>' && cmd->str[i + 1] == '>')
			cmd->spc[REDAPP] = 1;
		else if (cmd->str[i] == '<' && cmd->str[i + 1] == '<')
			cmd->spc[HERDOC] = 1;
		else if (cmd->str[i] == '>' && cmd->str[i - 1] != '>')
			cmd->spc[REDIN] = 1;
		else if (cmd->str[i] == '<' && cmd->str[i - 1] != '<')
			cmd->spc[REDOUT] = 1;
		i++;
	}
}

/*##############################################################################
#	Tokenizer receives shell struct, cycles through all commands and
		fill their fields. Every command struct should have a
		str, which stores input with the operator at the end
############################################################################*/
void	print_arguments_and_flags(t_command *cmd)
{
	int	i = 0;
	char *ar[] = {"PIPE  ", "SQUOTE", "DQUOTE", "MQUOTE",
			"REDIN ", "REDOUT", "REDAPP", "HERDOC"};
	char *co[] = {"-XX- FALSE", "-\\/-   --:   TRUE"};
	while (cmd->arguments[i])
		debug(cmd->arguments[i++]);
	debug("past");
	i = 0;
	while (i < 8)
		printf("%s: %s\n", ar[(i - 1) % 8], co[cmd->spc[i++] % 2]);
}

int	parser(t_hellmini *sh)
{
	t_command	*cmd;
	int			args;

	cmd = sh->current_cmd;
	while (cmd && cmd != NULL)
	{
		args = split_string(cmd);
		if (!args)
			return (FAIL);
		set_command_name(cmd);
		set_arguments(cmd, args);
		init_flags(cmd);
		set_cmd_flags(cmd);
		//print_arguments_and_flags(cmd);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

/*int	main(int argc, char **argv){
	t_hellmini *shell;
	t_command *cmd;
	char	*str = "echo -n 'debbing' |\0";

	shell = (t_hellmini *)malloc(sizeof(t_hellmini));
	cmd = (t_command *)malloc(sizeof(t_command));
	shell->current_cmd = cmd;
	cmd->str = argv[1];
	cmd->next = NULL;
	//printf("%s\n", cmd->str);
	int o = parser(shell);
	printf("SS: %d\n", o);
	return (0);
}*/