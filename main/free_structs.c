
#include "./../global.h"

static void	free_things_inside_command(t_command *cmd)
{
	int	i;

	if (cmd->str)
		free(cmd->str);
	if (cmd->command)
		free(cmd->command);
	if (cmd->next)
		free(cmd->next);
	if (cmd->prev)
		free(cmd->prev);

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
}

void	free_commands(t_hellmini *shell)
{
	t_command	*cmd;
	t_command	*nxt;
	t_command	*pre;

	cmd = shell->current_cmd;
	nxt = NULL;
	pre = NULL;
	while (cmd)
	{
		if (cmd->next)
			nxt = cmd->next;
		free_things_inside_command(cmd);
		if (nxt)
			cmd = nxt;
		else
			cmd = NULL;
	}
	free(shell->current_cmd);
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
