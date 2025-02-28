#include "minishell.h"

void	cd_too_many_arg(t_ms *ms)
{
	ft_print_error("cd : too many arguments\n", NULL, NULL);
	ms->exit_status = 1;
	return (ft_builtins_exit(ms, NULL, 1));
}

void	cd_home(t_ms *ms)
{
	if (!ft_getenv(ms, "HOME"))
	{
		ft_print_error("cd: HOME not set\n", NULL, NULL);
		return (ft_builtins_exit(ms, NULL, 1));
	}
	if (chdir(ft_getenv(ms, "HOME")) == -1)
		return (ft_builtins_exit(ms, NULL, 1));
}

void	cd_back_to_oldpwd(t_ms *ms)
{
	if (!ft_getenv(ms, "OLDPWD"))
	{
		ft_print_error("cd: OLDPWD not set\n", NULL, NULL);
		return (ft_builtins_exit(ms, NULL, 1));
	}
	if (chdir(ft_getenv(ms, "OLDPWD")) == -1)
		return (ft_builtins_exit(ms, NULL, 1));
}

void	cd_command(t_ms *ms, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->cmd_size > 2)
		return (cd_too_many_arg(ms));
	if (!cmd->cmd[1] || !*cmd->cmd[1]
		|| (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "~") == 0)
		|| (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "--") == 0))
		return (cd_home(ms));
	else if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-") == 0)
	{
		cd_back_to_oldpwd(ms);
		printf("%s\n", ft_getenv(ms, "OLDPWD"));
		ft_update_pwd(ms);
	}
	else if (ft_check_valid_dir(ms, cmd, &path))
	{
		if (chdir(path) == -1)
			return (ft_builtins_exit(ms, NULL, 1));
		ft_update_pwd(ms);
	}
	ft_builtins_exit(ms, NULL, 0);
}
