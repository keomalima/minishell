#include "minishell.h"

static char	*get_exec_path(char *path, char *cmd)
{
	char	*prefixed_path;
	char	**path_env;
	int		i;

	if (!path || !cmd[0] || ft_is_only_space(path))
		return (NULL);
	path_env = ft_split(path + 5, ':');
	if (!path_env)
		return (NULL);
	i = 0;
	while (path_env[i])
	{
		prefixed_path = ft_join_path(path_env[i], cmd);
		if (!prefixed_path)
			break ;
		if (access(prefixed_path, X_OK) == 0)
		{
			free_split(path_env);
			return (prefixed_path);
		}
		free(prefixed_path);
		i++;
	}
	free_split(path_env);
	return (NULL);
}

int	is_valid_string(const char *str)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, "..")
		|| !ft_strcmp(str, "...") || !ft_strcmp(str, "...."))
		return (0);
	return (1);
}

static void	dir_check(t_ms *ms, const char *path)
{
	struct stat	path_stat;

	if (!stat(path, &path_stat))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_print_error("minishell: ", (char *)path,
				": Is a directory\n");
			exit_handler(ms, 126);
		}
	}
	else
	{
		ft_print_error("minishell: ", (char *)path,
			": No such file or directory\n");
		exit_handler(ms, 127);
	}
}

void	check_path(t_ms *ms, t_cmd *cmd, char **exec_path, char *path)
{
	if (cmd->cmd[0])
	{
		if (ft_strcmp(cmd->cmd[0], "0") != 0 && access(cmd->cmd[0], X_OK) == 0)/// weird behavior here!
		{
			*exec_path = ft_strdup(cmd->cmd[0]);
			if (!exec_path)
				exit_handler(ms, 12);
		}
		else
			*exec_path = get_exec_path(path, cmd->cmd[0]);
	}
	else
		*exec_path = get_exec_path(path, cmd->cmd[0]);
	if (!*exec_path || !is_valid_string(cmd->cmd[0]))
	{
		if (*exec_path)
			free(*exec_path);
		error_handler(ms, cmd->cmd, path);
	}
}

char	**parse_arg(t_cmd *cmd, t_ms *ms)
{
	char	*exec_path;
	char	*path;

	if (is_builtin_cmd(cmd->cmd[0]))
		return (cmd->cmd);
	if (ft_strchr(cmd->cmd[0], '/'))
		dir_check(ms, cmd->cmd[0]);
	exec_path = NULL;
	path = ft_getenv(ms, "PATH");
	check_path(ms, cmd, &exec_path, path);
	free(cmd->cmd[0]);
	cmd->cmd[0] = exec_path;
	return (cmd->cmd);
}
