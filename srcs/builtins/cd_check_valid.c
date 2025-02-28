#include "minishell.h"

static char	*ft_retrieve_home_path(t_ms *ms, t_cmd *cmd)
{
	char	*home;
	char	*dest;
	char	*path;

	home = ft_getenv(ms, "HOME");
	if (!home)
	{
		ft_print_error("cd: HOME not set\n", NULL, NULL);
		ft_builtins_exit(ms, NULL, 1);
		return (NULL);
	}
	path = (cmd->cmd[1]) + 1;
	dest = ft_strjoin(home, path);
	if (!dest)
	{
		ft_builtins_exit(ms, NULL, 12);
		return (NULL);
	}
	return (dest);
}

static int	ft_check_existing_dir(char *path, t_ms *ms)
{
	ft_print_error("cd: ", path, ": No such file or directory\n");
	ms->exit_status = 1;
	ft_free(&path);
	ft_builtins_exit(ms, NULL, 1);
	return (0);
}

static int	ft_check_is_dir(char *path, t_ms *ms)
{
	ft_print_error("cd: ", path, ": Not a directory\n");
	ms->exit_status = 1;
	ft_free(&path);
	ft_builtins_exit(ms, NULL, 1);
	return (0);
}

static int	ft_check_acces(char *path, t_ms *ms)
{
	ft_print_error("cd: ", path, ": Permission denied\n");
	ms->exit_status = 1;
	ft_free(&path);
	ft_builtins_exit(ms, NULL, 1);
	return (0);
}

int	ft_check_valid_dir(t_ms *ms, t_cmd *cmd, char **path)
{
	struct stat	sb;

	if (cmd->cmd[1] && *cmd->cmd[1] && *cmd->cmd[1] == '~')
	{
		*path = ft_retrieve_home_path(ms, cmd);
		if (!*path)
		{
			ft_builtins_exit(ms, NULL, 1);
			return (0);
		}
	}
	else
		*path = cmd->cmd[1];
	if (stat(*path, &sb) == -1)
		return (ft_check_existing_dir(*path, ms));
	if (!S_ISDIR(sb.st_mode))
		return (ft_check_is_dir(*path, ms));
	if (access(*path, X_OK) == -1)
		return (ft_check_acces(*path, ms));
	return (1);
}
