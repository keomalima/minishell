/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:52:06 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 13:00:47 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + add_slash + 1);
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

static void	error_handler_2(t_ms *ms, char **cmd)
{
	if (!ft_strcmp(cmd[0], "."))
	{
		ft_print_error("minishell: ", cmd[0], ": filename argument required\n");
		exit_handler(ms, 2);
	}
	else
	{
		ft_print_error("minishell: ", cmd[0], ": command not found\n");
		exit_handler(ms, 127);
	}
}

void	error_handler(t_ms *ms, char **cmd, char *path)
{
	if (!path || ft_is_only_space(path))
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
	else if (cmd[0] && access(cmd[0], X_OK) != 0 && ft_strlen(cmd[0]) > 2
		&& access(cmd[0] + 2, F_OK) == 0)
	{
		ft_print_error("minishell: ", cmd[0], ": Permission denied\n");
		exit_handler(ms, 126);
	}
	else if (cmd[0])
		error_handler_2(ms, cmd);
}

int	is_valid_string(const char *str)
{
	if (!ft_strcmp(str, ".") || !ft_strcmp(str, "..")
		|| !ft_strcmp(str, "...") || !ft_strcmp(str, "...."))
		return (0);
	return (1);
}
