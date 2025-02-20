#include "minishell.h"
int	is_builtin_cmd(char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env"));
}

int	is_builtin_env_cmd(t_ms *ms, char *cmd)
{
	if (ms->cmd->cmd_size == 1)
		return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
	return (0);
}

void	exec_builtin(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "echo"))
		echo_command(ms, ms->cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "pwd"))
		pwd_command(ms, cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "export"))
		export_command(ms, cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "cd"))
		cd_command(ms, cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "unset"))
		unset_command(ms, cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "env"))
		env_command(ms);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "exit"))
		exit_command(ms, cmd);
}
