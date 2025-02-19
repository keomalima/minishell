#include "minishell.h"

void	echo_command(t_ms *ms, t_cmd *cmd)
{
	int	nl;
	int	i;
	int	j;

	nl = 1;
	i = 1;
	while (cmd->cmd[i] && cmd->cmd[i][0] == '-' && cmd->cmd[i][1] == 'n')
	{
		j = 1;
		while (cmd->cmd[i][j] == 'n')
			j++;
		if (cmd->cmd[i][j] != '\0')
			break ;
		nl = 0;
		i++;
	}
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[(i++) + 1])
			printf(" ");
	}
	if (nl)
		printf("\n");
	ft_builtins_exit(ms, 0);
}
