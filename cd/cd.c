
#include "./../global.h"

/*

#### Possible parameters CD

	. only absolute or relative path

*/

int	absolute_path(char *path)
{
	int	op_code;

	op_code = chdir(path);
	return (op_code);
}

int	relative_path(char *path)
{
	int	op_code;

	op_code = chdir(path);
	return (op_code);
}

int	cmd_cd(t_command *cmd)
{
	int	op_code;

	// errors definer
	op_code = 0;
	if (cmd->args[1][0] == '/')
		op_code = absolute_path(cmd->args[1]);
	else
		op_code = relative_path(cmd->args[1]);

	if (op_code != 0)
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		
	//printf("ECODE %d\n", op_code);
	printf("CWD: %s\n", getcwd(NULL, 0));
	return (0);
}

void	stradd(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i++])
		s1[i - 1] = s2[i - 1];
}

int main(int argc, char *argv[]) 
{
	t_command *cmd;

	cmd = (t_command *)malloc(sizeof(t_command));

	stradd(cmd->args[0], "cd\0");
	if (argc >= 2)
		stradd(cmd->args[1], argv[1]);
	else if (argv[1] == NULL)
		stradd(cmd->args[1], getenv("HOME"));
	stradd(cmd->args[2], "\0");

	cmd_cd(cmd);
	free(cmd);
	return (0);
}
