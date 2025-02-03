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

void	error_handler(t_ms *ms, char **cmd)
{
	(void)ms;
	if (cmd[0] && ft_strncmp(cmd[0], "/", 1) == 0)
	{
		ft_printf("%s: %s\n", strerror(errno), cmd[0]);
		exit_handler(ms, 128);
	}
	else if (cmd[0])
	{
		ft_printf("command not found: %s\n", cmd[0]);
		exit_handler(ms, 128);
	}
	else
	{
		ft_printf("permission denied: \n");
		exit_handler(ms, 126);
	}
}

char	**parse_arg(t_cmd *cmd, t_ms *ms)
{
	char	*exec_path;
	char	*path;

	exec_path = NULL;
	path = getenv("PATH");
	if (cmd->cmd[0])
	{
		if (access(cmd->cmd[0], X_OK) == 0)
			exec_path = ft_strdup(cmd->cmd[0]);
		else
			exec_path = get_exec_path(path, cmd->cmd[0]);
	}
	else
		exec_path = get_exec_path(path,cmd->cmd[0]);
	if (!exec_path)
		error_handler(ms, cmd->cmd);
	free(cmd->cmd[0]);
	cmd->cmd[0] = exec_path;
	return (cmd->cmd);
	return (NULL);
}