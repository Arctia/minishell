
#include "../global.h"

/*##############################################################################
#	Help Functions
##############################################################################*/

int	until_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_not_space(str[i]))
		i++;
	return (i);
}

void	move_to_next_char(char *str)
{
	while (str[0] && ft_is_space(str[0]))
		str++;
}

/*##############################################################################
#	Set command name
##############################################################################*/
static void	set_command_name(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->command = (char *) malloc(sizeof(char) * ft_strlen(cmd->split[0]) + 1);
	while (cmd->split[0][i++])
		cmd->command[i - 1] = cmd->split[0][i - 1];
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
		cmd->arguments[i - 1] = (char *) malloc(sizeof(char) *
			ft_strlen(cmd->split[i]) + 1);
		if (cmd->arguments[i - 1])
		{
			free(cmd->arguments);
			return ;
		}
		j = 0;
		while (cmd->split[i][j++])
			cmd->arguments[i - 1][j - 1] = cmd->split[i][j - 1];
		cmd->arguments[i - 1][j] = '\0';
		i++;
	}
}

/*##############################################################################
#	Splitter Functions
##############################################################################*/


/* __ items in string ___________________?______________________________________
		. return number of items to be stored
_________________________________________!___________________________________ */
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
		if (ft_is_not_space(str[i]) && !in_word)
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
_________________________________________!___________________________________ */
void	write_word_expander(char *cnt, char *str)
{
	char	fchar;
	int		i;

	i = 0;
	fchar = str[0];
	while (ft_is_not_space(str[0]))
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

void	write_word(char *cnt, char *str)
{
	int	i;

	i = 0;
	while (ft_is_not_space(str[0]))
		cnt[i++] = str++[0];
	cnt[i] = '\0';
}

/* __ split string ______________________?______________________________________
		. Count items to be store and allocate them
		. Allocate every single item
		. Write them
_________________________________________!___________________________________ */
int	split_string(t_command *cmd)
{
	char	*init;
	int		items;
	int 	c;

	init = cmd->str;
	move_to_next_char(cmd->str);
	items = items_in_string(cmd->str);
	cmd->split = (char **) malloc(sizeof(char *) * items + 1);
	if (!(cmd->split))
		return (0);
	c = 0;
	while (cmd->str[0])
	{
		cmd->split[c] = (char *) malloc(sizeof(char) *
			until_space(cmd->str) + 1);
		if (!(cmd->split[c]))
			return (0);
		write_word(cmd->split[c], cmd->str);
		c++;
	}
	cmd->split[c] = NULL;
	cmd->str = init;
	return (items);
}

/*##############################################################################
#	Tokenizer receives shell struct, cycles through all commands and
		fill their fields. Every command struct should have a
		str, which stores input with the operator at the end.
##############################################################################*/

int	parser(t_hellmini *sh)
{
	t_command	*cmd;
	int			args;

	cmd = sh->current_cmd;
	// tokenizer
	while (cmd)
	{
		args = split_string(cmd);
		if (!args)
			return (FAIL);
		set_command_name(cmd);
		//set_flags(&cmd);
		set_arguments(cmd, args);
		cmd = cmd->next;
	}
	// actual parser
	return (SUCCESS);
}

int	main(){
	printf("test");
	return (0);
}