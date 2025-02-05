#include "minishell.h"

int	ft_check_valid_dir(t_ms *ms, t_cmd *cmd)
{
	struct stat	sb;

	if (stat(cmd->cmd[1], &sb) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		errno = 0;
		if (ms->cmd_count > 1)
			exit_handler(ms, 1);
		return (0);						///// have to free before return ??
	}
	if (!S_ISDIR(sb.st_mode))
	{
		printf("cd: %s: Not a directory\n", cmd->cmd[1]);
		errno = 0;
		if (ms->cmd_count > 1)
			exit_handler(ms, 1);
		return (0);						///// have to free before return ??
	}
	if (access(cmd->cmd[1], X_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", cmd->cmd[1]);
		errno = 0;
		if (ms->cmd_count > 1)
			exit_handler(ms, 1);
		return (0);						///// have to free before return ??
	}
	return (1);
}

void	cd_command(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd_size > 2)
	{
		printf("cd : too many arguments\n");
		exit_handler(ms, 1);
	}
	else if (!cmd->cmd[1] || !*cmd->cmd[1])
	{
		if (!getenv("HOME"))
			printf("cd: HOME not set\n");
		if (chdir(getenv("HOME")) == -1)
		{
			if (ms->cmd_count > 1)
				exit_handler(ms, 1);
		}
	}
	else
	{
		if (ft_check_valid_dir(ms, cmd))
			chdir(cmd->cmd[1]);
	}
	if (ms->cmd_count > 1)
		exit_handler(ms, 0);
}
