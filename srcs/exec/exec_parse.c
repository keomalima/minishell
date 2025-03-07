#include "minishell.h"

char	*ft_join_path(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		add_slash;

	if (!s1 || !s2)
		return (NULL);
	add_slash = (s1[ft_strlen(s1) - 1] != '/');
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + add_slash + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	if (add_slash)
		str[j++] = '/';
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*get_exec_path(char *path, char *cmd)
{
	char	*prefixed_path;
	char	**path_env;
	int		i;

	if (!path || ft_is_only_space(path))
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

void	error_handler(t_ms *ms, char **cmd, char *path)
{
	if (!path  || ft_is_only_space(path))
	{
		ft_print_error("minishell: ", cmd[0], ": No such file or directory\n");
		exit_handler(ms, 127);
	}
	else if (cmd[0] && ft_strncmp(cmd[0], "/", 1) == 0)
	{
		ft_print_error(cmd[0], ": ", strerror(errno));
		ft_print_error("\n", NULL, NULL);
		exit_handler(ms, 127);
	}
	else if (cmd[0] && access(cmd[0], X_OK) != 0 && ft_strlen(cmd[0]) > 2 && access(cmd[0] + 2, F_OK) == 0)
	{
		ft_print_error("minishell: ", cmd[0], ": Permission denied\n");
		exit_handler(ms, 126);
	}
	else if (cmd[0])
	{
		ft_print_error("minishell: ", cmd[0], ": command not found\n");
		exit_handler(ms, 127);
	}
}

void dir_check(t_ms *ms, const char *path)
{
	struct stat path_stat;

	if (!stat(path, &path_stat))
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_print_error("minishell: ", (char *)path, ": Is a directory\n");
			exit_handler(ms, 126);
		}
	}
	else
	{
		ft_print_error("minishell: ", (char *)path, ": No such file or directory\n");
		// ft_print_error("minishell: ", (char *)path, ": Is not a directory\n");
		exit_handler(ms, 127);
	}
}

char	**parse_arg(t_cmd *cmd, t_ms *ms)
{
	char	*exec_path;
	char	*path;

	if (is_builtin_cmd(cmd->cmd[0]))
		return (cmd->cmd);
	if (ft_strchr(cmd->cmd[0], '/'))
		dir_check(ms, cmd->cmd[0]) ;
	exec_path = NULL;
	path = ft_getenv(ms, "PATH");
	// printf("		--> command {%s}\n", cmd->cmd[0]);
	if (cmd->cmd[0])
	{
		if (ft_strcmp(cmd->cmd[0], "0") != 0 && access(cmd->cmd[0], X_OK) == 0)				/// weird behavior here!
			exec_path = ft_strdup(cmd->cmd[0]);
		else
			exec_path = get_exec_path(path, cmd->cmd[0]);
	}
	else
		exec_path = get_exec_path(path, cmd->cmd[0]);
	if (!exec_path)
		error_handler(ms, cmd->cmd, path);
	free(cmd->cmd[0]);
	cmd->cmd[0] = exec_path;
	return (cmd->cmd);
}
