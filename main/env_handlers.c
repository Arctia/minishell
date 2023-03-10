#include "../global.h"

//
void	init_shell_env(char **or_env, t_hellmini shell)
{
	int		i;
	//int		j;
	char	*lvl;

	//ft_putstr_fd("Dioboia",1);
	shell.env = ft_arrdup(or_env);
	if (!shell.env)
	{
		write(1, "Error!Not enough memory to set env\n", 36);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (or_env[i])
	{
		if (!ft_strncmp(or_env[i], "SHLVL=", 6))
		{
			lvl = ft_strtrim(or_env[i], "SHLVL=");
			shell.env[i] = ft_strjoin("SHLVL=", (ft_strdup(ft_itoa(ft_atoi(lvl) + 1))));
		}
		i++;
	}
	//for feedback only
	//ft_putstr_fd(shell.env[2], 1);
	//ft_putstr_fd(shell.env[3], 1);
	free(lvl);
}
