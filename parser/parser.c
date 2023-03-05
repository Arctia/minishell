
#include "./../global.h"

/* To Do
	1. Split the string into a matrix! Is easier. That way you can delimit 
		double or single quotes directly. Then the first item goes into cmd, 
		then if the first character of next items is "-" store them into flags 
		and then only arguments..
		While doing it:
			- if encountering a space split and store the item in a matrix
				quite simple, right? Yeah need to consider double and single
				quote/s while doing that, if encountering one, wait until is
				closed.
			- if the double quote closes and the next character is adjacent (no 
				space between them) remove the quote and keep going until 
				space is found. Same applies to quotes inside a word!
			- do not consider quotes inside quotes!
	2. Parser check syntax (?)
	3. ...
*/

/*##############################################################################
#	Help Functions
##############################################################################*/

int	until_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t') // etc ..
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
	char	*name;
	int		i;

	i = 0;
	name = (char *) malloc(sizeof(char) * until_space(cmd->str));
	while (ft_not_space(cmd->str[0]))
	{
		name[i++] = cmd->str[0];
		cmd->str++;
	}
	name[i] = '\0';
	cmd->command = name;
	move_to_next_char(cmd->str);
}

/*##############################################################################
#	Set Flags
		° need to consider one or double '-' flags
##############################################################################*/
static int	how_many_flags(const char *str)
{
	int	flags_n;
	int	i;

	i = 0;
	flags_n = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]))
			i++;
		else if (str[i] == '-' && str[i + 1] && ft_not_space(str[i + 1]))
		{
			i++;
			flags_n += 1;
			while (str[i] && ft_not_space(str[i]))
				i++;
		}
		else
			break ;
	}
	return (flags_n);
}

static void	set_flags(t_command *cmd)
{
	char	**flags;
	int		flags_n;
	int		i;
	int		j;

	flags_n = how_many_flags(cmd->str);
	if (flags_n < 1)
		return ;
	flags = (char **) malloc(sizeof(char *) * flags_n);
	i = 0;
	j = 0;
	while (flags_n > 0)
	{
		j = 0;
		flags[i] = ft_calloc(sizeof(char), until_space(cmd->str));
		while (ft_not_space(cmd->str[0]))
		{
			flags[i][j++] = cmd->str[0];
			cmd->str++;
		}
		move_to_next_char(cmd->str);
		flags_n -= 1;
		i += 1;
	}
	cmd->flags = flags;
}

/*##############################################################################
#	Set Arguments
		° slide string and obtain
##############################################################################*/
static void	set_arguments(t_command *cmd)
{

}

/*##############################################################################
#	Tokenizer receives shell struct, cycles through all commands and
		fill their fields. Every command struct should have a
		str, which stores input with the operator at the end.
##############################################################################*/
int	parser(t_hellmini *sh)
{
	t_command	*cmd;

	cmd = sh->current_cmd;
	// tokenizer
	while (cmd)
	{
		set_command_name(&cmd);
		set_flags(&cmd);
		set_arguments(&cmd);
		cmd = cmd->next;
	}
	// parser --> syntax checker
}

int	main()
{
	return (0);
}