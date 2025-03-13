/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:04:39 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 11:04:40 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**set_path_env(char *path)
{
	char	**path_env;

	if (ft_strncmp(path, "/home", ft_strlen("/home")) == 0)
		path_env = ft_split(path + 5, ':');
	else
		path_env = ft_split(path, ':');
	if (!path_env)
		return (NULL);
	return (path_env);
}

static char	*get_exec_path(char *path, char *cmd)
{
	char	*prefixed_path;
	char	**path_env;
	int		i;

	if (!path || !cmd[0] || ft_is_only_space(path))
		return (NULL);
	path_env = set_path_env(path);
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

static void	check_path(t_ms *ms, t_cmd *cmd, char **exec_path, char *path)
{
	if (cmd->cmd[0])
	{
		if (access(cmd->cmd[0], X_OK) == 0)
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
