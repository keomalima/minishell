#include "minishell.h"

void	echo_command(t_ms *ms, t_cmd *cmd)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (ft_strcmp(cmd->cmd[1], "-n") == 0)
	{
		i++;
		nl = 0;
	}
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		i++;
		if (cmd->cmd[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (ft_builtins_exit(ms, NULL, 0));
}
