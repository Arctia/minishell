
#include "../global.h"
// ' ’ ’ preserves the literal value of each character within the quotes.
//A single quote may not occur between single quotes, even when preceded by a backslash.
// ‘ " ’ preserves the literal value of all characters within the quotes,
//with the exception of ‘$’, ‘‘’, ‘\’, and, when history expansion is enabled, ‘!’
//

//keeps monitoring whether str[i] is outside(x % 2 == 0) or inside(== 1)a quoting sequence.then
//	if (outside(or as soon as closed) && next char is either a space or EOL)
//			tokenz++;
int	tkn_nbr(char *str)
{
	int	i;
	int	n_tkn;
	int	quotes;
	int	w_quotes;


	i = -1;
	n_tkn = 0;
	quotes = 0;
	w_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !quotes)
			w_quotes = (w_quotes + 1) % 2;
		else if (str[i] == '\'' && !w_quotes)
			quotes = (quotes + 1) % 2;
		if ((!quotes && !w_quotes) && !(str[i] == ' ')
			&& ((str[i + 1] == ' ') || !str[i + 1]))
			n_tkn++;
	}
	return (n_tkn);
}

//count the lenght until the first occurence of char
//(mainly to get the size necessary to malloc tokens)
int	ft_strchr_len(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] == c))
			break ;
	return (i);
}

//read the string and store the number of pipes, quotes and double quotes
//inside an array;
t_command	* count_pqwq(t_command *command, char *str)
{
	int	i;
	//int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			command->mc_pipes++;
		if (str[i] == '\'')
			command->mc_quotes++;
		if (str[i] == '\"')
			command->mc_wquotes++;
	}
	printf("Pipes: %d\n",command->mc_pipes);
	printf("Quotes: %d\n",command->mc_quotes);
	printf("Double quotes: %d\n",command->mc_wquotes);
	return (command);
}

int	rip_and_tear(t_command *command, char *str)
{
	int	i;
	int	n_cmds;

	i = 0;
	n_cmds = 1;
	if ((count_pqwq(command, str))->mc_quotes % 2
		|| (count_pqwq(command, str))->mc_wquotes % 2)
		write(2, "syntax error, odd number of quotes or double quotes\n", 53);
	// while (str[i])
	// {
	// 	while (str[i] != )
	// }
	return (0);
}
