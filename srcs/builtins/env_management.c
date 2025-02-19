#include "minishell.h"

int	ft_find_var(char *name, t_ms *ms)
{
	int		i;
	int		comp;

	i = 0;
	while (ms->env[i])
	{
		comp = ft_strncmp(ms->env[i], name, ft_strlen(name));
		if (comp == 0)
			return (i);
		i++;
	}
	return (-1);
}

size_t	ft_env_count(char **env)
{
	size_t	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**ft_duplicate_env(t_ms *ms, char **env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc((ft_env_count(env) + 1), sizeof(char *));
	if (!new_env)
		exit_handler(ms, 12);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_split(new_env);
			exit_handler(ms, 12);
		}
		i++;
	}
	return (new_env);
}
