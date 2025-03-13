/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:45:59 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 12:51:16 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fill_unset(int index, char **new_env, t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		new_env[i] = ft_strdup(ms->env[i]);
		if (!new_env[i])
		{
			free_split(new_env);
			ft_builtins_exit(ms, NULL, 12);
			exit (12);
		}
	}
	index++;
	while (ms->env[index])
	{
		new_env[i++] = ft_strdup(ms->env[index++]);
		if (!new_env[i - 1])
		{
			free_split(new_env);
			ft_builtins_exit(ms, NULL, 12);
			exit (12);
		}
	}
	return (1);
}

static char	**ft_delete_env(int index, t_ms *ms)
{
	char	**new_env;

	new_env = ft_calloc((ft_env_count(ms->env)), sizeof(char *));
	if (!new_env)
	{
		ft_builtins_exit(ms, NULL, 12);
		exit (12);
	}
	ft_fill_unset(index, new_env, ms);
	return (new_env);
}

static int	ft_unset_env(t_ms *ms, char	*var)
{
	int		index;
	char	**new_env;

	index = ft_find_var(var, ms);
	if (index < 0)
		return (1);
	else
	{
		new_env = ft_delete_env(index, ms);
		if (!new_env)
			return (0);
		free_split(ms->env);
		ms->env = new_env;
	}
	return (1);
}

void	unset_command(t_ms *ms, t_cmd *cmd)
{
	size_t	i;

	if (cmd->cmd[1])
	{
		i = 1;
		while (cmd->cmd[i])
		{
			if (!ft_unset_env(ms, cmd->cmd[i]))
				return (ft_builtins_exit(ms, NULL, 1));
			i++;
		}
	}
	ft_builtins_exit(ms, NULL, 0);
}
