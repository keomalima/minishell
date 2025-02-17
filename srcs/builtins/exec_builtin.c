#include "minishell.h"

int	is_builtin_cmd(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	solo_builtin(t_ms *ms)
{
	if (!ms->cmd)
		return (0);
	else if (ms->cmd->cmd[0] && is_builtin_cmd(ms->cmd->cmd[0])
		&& ms->cmd_count == 1)
	{
		if (ft_strcmp(ms->cmd->cmd[0], "cd") == 0)
			cd_command(ms, ms->cmd);
		else if (ft_strcmp(ms->cmd->cmd[0], "pwd") == 0)
			pwd_command(ms);
		else if (ft_strcmp(ms->cmd->cmd[0], "export") == 0)
			export_command(ms, ms->cmd);
		else if (ft_strcmp(ms->cmd->cmd[0], "unset") == 0)
			unset_command(ms, ms->cmd);
		else if (ft_strcmp(ms->cmd->cmd[0], "env") == 0)
			env_command(ms);
		else if (ft_strcmp(ms->cmd->cmd[0], "echo") == 0)
			echo_command(ms, ms->cmd);
		else if (ft_strcmp(ms->cmd->cmd[0], "exit") == 0)
			exit_command(ms, ms->cmd);
		return (1);
	}
	return (0);
}

void	exec_builtin(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "cd") == 0)
		cd_command(ms, cmd);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "pwd") == 0)
		pwd_command(ms);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "export") == 0)
		export_command(ms, cmd);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "unset") == 0)
		unset_command(ms, cmd);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "env") == 0)
		env_command(ms);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "echo") == 0)
		echo_command(ms, ms->cmd);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "exit") == 0)
		exit_command(ms, cmd);
}
