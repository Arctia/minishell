#include "./../global.h"

void	stradd(char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i++])
		s1[i - 1] = s2[i - 1];
}

/* CD into previous folder, return 0 if not "-\0" is found */
int	cmd_cd_previous_folder(char cmd[2048][2048], char previous_folder[88])
{
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		if (previous_folder[0] == 0)
		{
			printf("cd: OLDPWD not set\n");
			return (-1);
		}
		else
		{
			chdir(previous_folder);
			printf("%s\n", previous_folder);
			return (1);
		}
	}
	return (0);
}

/* CD Command, previous_folder stores the last folder visited */
int	cmd_cd(t_command *cmd)
{
	static char	previous_folder[88];
	char		actual_folder[88];
	int			op_code;
	int			pf_code;

	stradd(actual_folder, getcwd(NULL, 0));
	op_code = -1;
	pf_code = cmd_cd_previous_folder(cmd->args, previous_folder);
	if (pf_code != 0)
	{
		if (pf_code == -1)
			return (1);
		op_code = 0;
	}
	else
		op_code = chdir(cmd->args[1]);
	if (op_code != 0)
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		return (1);
	}
	stradd(previous_folder, actual_folder);
	printf("CWD: %s\n", getcwd(NULL, 0));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
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
