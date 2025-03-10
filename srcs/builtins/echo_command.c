#include "minishell.h"

static void	ft_handle_n(t_cmd *cmd, int *nl, int *i)
{
	int	j;

	while (cmd->cmd[*i] && cmd->cmd[*i][0] == '-' && cmd->cmd[*i][1] == 'n')
	{
		j = 1;
		while (cmd->cmd[*i][j] == 'n')
			j++;
		if (cmd->cmd[*i][j] != '\0')
			break ;
		*nl = 0;
		*i += 1;
	}
}

void	echo_command(t_ms *ms, t_cmd *cmd)
{
	int		nl;
	int		i;
	ssize_t	ret;

	nl = 1;
	i = 1;
	ft_handle_n(cmd, &nl, &i);
	//signal(SIGPIPE, SIG_IGN);
	while (cmd->cmd[i])
	{
		ret = write(STDOUT_FILENO, cmd->cmd[i], ft_strlen(cmd->cmd[i]));
		if (ret == -1)
			return;
		if (cmd->cmd[i + 1])
		{
			ret = write(STDOUT_FILENO, " ", 1);
			if (ret == -1)
			{
				perror("write error");
				return;
			}
		}
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	ft_builtins_exit(ms, NULL, 0);
	ms->exit_status = 0;
}

