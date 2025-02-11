#include "minishell.h"

int	ft_check_valid_dir(t_ms *ms, t_cmd *cmd)
{
	struct stat	sb;

	if (stat(cmd->cmd[1], &sb) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		printf("cd: %s: Not a directory\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	if (access(cmd->cmd[1], X_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	return (1);
}

void	cd_command(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd_size > 2)
	{
		printf("cd : too many arguments\n");
		return (ft_builtins_exit(ms, NULL, 1));
	}
	if (!cmd->cmd[1] || !*cmd->cmd[1])
	{
		if (!ft_getenv(ms, "HOME"))
			printf("cd: HOME not set\n");
		if (chdir(ft_getenv(ms, "HOME")) == -1)
			return (ft_builtins_exit(ms, NULL, 1));
	}
	else
	{
		// if (ft_check_valid_dir(ms, cmd))
		// {
			if (chdir(cmd->cmd[1]) == -1)
			{
				perror("cd");
				ft_builtins_exit(ms, NULL, 1);
			}
				// printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
			else if (getcwd(NULL, 0) == NULL)
				printf("chdir: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		// }
	}
	ft_builtins_exit(ms, NULL, 0);
}


