
#include "./../global.h"

static void	free_things_inside_command(t_command *cmd)
{
	int	i;

	if (cmd->str != NULL)
		free(cmd->str);
	if (cmd->command != NULL)
		free(cmd->command);
	i = 0;
	if (cmd->tokens != NULL)
	{
		while (cmd->tokens[i])
			free(cmd->tokens[i++]);
		free(cmd->tokens);
	}
	i = 0;
	if (cmd->arguments != NULL)
	{
		while (cmd->arguments[i])
				free(cmd->arguments[i++]);
		free(cmd->arguments);
	}
	free(cmd);
}

void	free_commands(t_hellmini *shell)
{
	t_command	*cmd;
	t_command	*nxt;

	cmd = shell->current_cmd;
	nxt = NULL;
	while (cmd)
	{
		nxt = cmd->next;
		free_things_inside_command(cmd);
		cmd = nxt;
	}
	shell->current_cmd = NULL;
}

/* env may need to be modified, 
	to do so we need to do an allocated
	copy of it */
void	free_shell(t_hellmini *shell)
{
	if (shell->input)
		free(shell->input);
	free_commands(shell);
	free(shell);
}
