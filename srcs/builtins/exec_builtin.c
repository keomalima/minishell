#include "minishell.h"

int	exec_builtin(t_ms *ms)
{
	if (ms->cmd)
	{
		if (ft_strcmp(ms->cmd->cmd[0], "cd") == 0 && ms->cmd_count == 1)
		{
			cd_command(ms, ms->cmd);
			return (1);
		}
		else if (ft_strcmp(ms->cmd->cmd[0], "export") == 0 && ms->cmd_count == 1)
		{
			export_command(ms, ms->cmd);
			return (1);
		}
		else if (ft_strcmp(ms->cmd->cmd[0], "unset") == 0 && ms->cmd_count == 1)
		{
			unset_command(ms, ms->cmd);
			return (1);
		}
		else if (ft_strcmp(ms->cmd->cmd[0], "env") == 0 && ms->cmd_count == 1)
		{
			env_command(ms);
			return (1);
		}
	}
	return (0);
}
