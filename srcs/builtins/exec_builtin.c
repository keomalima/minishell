#include "minishell.h"

int	is_builtin_cmd(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int	solo_builtin(t_ms *ms)
{
	if (!ms->cmd)
		return (0);
	else if (!ft_strcmp(ms->cmd->cmd[0], "export")
		&& (ft_all_arg_null(ms->cmd->cmd)
		&& ft_count_arg(ms->cmd->cmd) == ms->cmd->nb_expand))
		return (0);
	else if (ms->cmd->cmd[0] && is_builtin_cmd(ms->cmd->cmd[0])
		&& ms->exec->cmd_count == 1)
	{
		file_handler(ms->cmd, ms, 0);
		if (!ft_strcmp(ms->cmd->cmd[0], "cd"))
			cd_command(ms, ms->cmd);
		else if (!ft_strcmp(ms->cmd->cmd[0], "unset"))
			unset_command(ms, ms->cmd);
		else if (!ft_strcmp(ms->cmd->cmd[0], "export"))
			export_command(ms, ms->cmd);
		else if (!ft_strcmp(ms->cmd->cmd[0], "env"))
			env_command(ms);
		else if (!ft_strcmp(ms->cmd->cmd[0], "exit"))
			exit_command(ms, ms->cmd);
		close_all_fds(ms);
		return (1);
	}
	return (0);
}

void	exec_builtin(t_ms *ms, t_cmd *cmd)
{
	if (!cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "echo"))
			echo_command(ms, ms->cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "pwd"))
			pwd_command(ms, cmd);
	else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "export"))
			export_command(ms, cmd);
	else if (ms->exec->cmd_count > 1)
	{
		if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "cd"))
			cd_command(ms, cmd);
		else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "unset"))
			unset_command(ms, cmd);
		else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "env"))
			env_command(ms);
		else if (cmd->cmd[0] && !ft_strcmp(cmd->cmd[0], "exit"))
			exit_command(ms, cmd);
	}
	if (ms->exec->cmd_count == 1 && is_builtin_cmd(cmd->cmd[0]))
		ft_builtins_exit(ms, 0);
}
