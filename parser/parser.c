
#include "../global.h"
#define GRN "\033[1;32m"
#define WHITE "\033[0m"

/*##############################################################################
#	Help Functions
############################################################################*/

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

char	ft_isquote(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return ('\0');
}

int	to_next_quote(char *str, int i, char quote)
{
	while (str[i] && str[i] != quote)
		i++;
	return (i);
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
	cmd->command[i - 1] = '\0';
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
		if (!cmd->arguments[i - 1])
		{
			free(cmd->arguments);
			return ;
		}
		j = 0;
		while (cmd->tokens[i][j++])
			cmd->arguments[i - 1][j - 1] = cmd->tokens[i][j - 1];
		cmd->arguments[i - 1][j - 1] = '\0';
		i++;
	}
	if (i == 1)
		cmd->arguments[0] = NULL;
}

/*##############################################################################
#	Splitter Functions
############################################################################*/
/* __ items in string ___________________?______________________________________
		. return number of items to be stored
		. single/double quotes TODO
_________________________________________!_________________________________ */
int	i_after_quote(char *str, int i, int *iw, int *in)
{
	char	c;

	c = str[i];
	if (*iw == 0 && str[i + 1] && str[i] != str[i + 1])
	{
		*iw = 1;
		*in = *in + 1;
	}
	i++;
	i = to_next_quote(str, i, c);
	return (i);
}

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
		if (ft_isquote(str[i]))
			i = i_after_quote(str, i, &in_word, &items_number);
		else if (ft_isnotspace(str[i]) && in_word == 0)
		{
			items_number++;
			in_word = 1;
		}
		else if (ft_isspace(str[i]))
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

// consider quotes!
void	write_word_old(char *cnt, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[0] && ft_isnotspace(cmd->str[0]))
	{
		cnt[i++] = cmd->str++[0];
	}
	cnt[i] = '\0';
}

void	write_word(char *cnt, t_command *cmd)
{
	int	i;
	int	t;
	int	c;

	i = 0;
	t = 0;
	c = 0;
	while (cmd->str[0])
	{
		if (ft_isquote(cmd->str[0]))
		{
			c = 0;
			t = to_next_quote(cmd->str, 1, cmd->str[0]);
			while (c++ <= t)
				cnt[i++] = cmd->str++[0];
		}
		else
			cnt[i++] = cmd->str++[0];
		if (ft_isspace(cmd->str[0]))
			break ;
	}
	cnt[i] = '\0';
}

/* __ split string ______________________?______________________________________
		. Count items to be store and allocate them
		. Allocate every single item
		. Write them
_________________________________________!_________________________________ */
int	split_string(t_command *cmd)
{
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
				* ft_strlen(cmd->str) + 1);
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

void	set_cmd_flags(t_command *cmd, int i)
{
	while (cmd->str[i])
	{
		if (cmd->str[i] == '|')
			cmd->spc[PIPE] = 1;
		else if (cmd->str[i] == '$')
			cmd->spc[CASH] = 1;
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
	int	i;
	char *ar[] = {"PIPE", "SQUOTE", "DQUOTE", "MQUOTE",
			"REDIN ", "REDOUT", "REDAPP", "HERDOC", "CASH"};
	char *co[] = {" ", GRN"TRUE"WHITE};
	i = 0;
	pfn("%2t command: '%s'", cmd->command);
	while (cmd->arguments[i])
	{
		pfn("%2t arg[%d]: '%s'", i, cmd->arguments[i]);
		i++;
	}
	i = 0;
	while (i < 9)
	{
		pfn("%t %-8s-->  %s", ar[(i) % 9], co[cmd->spc[i] % 2]);
		i++;
	}
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
		set_cmd_flags(cmd, 0);
		print_arguments_and_flags(cmd);
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