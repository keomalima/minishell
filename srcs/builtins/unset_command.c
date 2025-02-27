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
			return (0);
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
			return (0);
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
		return (NULL);
	}
	ft_fill_unset(index, new_env, ms);
	return (new_env);
}

static int	ft_unset_env(t_ms *ms, char	*var)
{
	int		index;

	index = ft_find_var(var, ms);
	if (index < 0)
		return (1);
	else
	{
		ms->env = ft_delete_env(index, ms);
		if (!ms->env)
			return (0);
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
