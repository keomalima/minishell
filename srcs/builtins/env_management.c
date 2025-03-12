#include "minishell.h"

int	ft_find_var(char *name, t_ms *ms)
{
	int		i;
	int		comp;

	i = 0;
	while (ms->env[i])
	{
		comp = ft_strncmp(ms->env[i], name, ft_strlen(name));
		if (comp == 0 && (!ms->env[i][ft_strlen(name)]
			|| (ms->env[i][ft_strlen(name)]
			&& ms->env[i][ft_strlen(name)] == '=')))
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

static void	ft_sort_env(char ***env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[i], (*env)[j]) < 0)
			{
				tmp = (*env)[i];
				(*env)[i] = (*env)[j];
				(*env)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**set_unset_env(void)
{
	char	**new_env;
	char	current_pwd[4096];

	new_env = ft_calloc(4, sizeof(char *));
	if (!new_env)
		exit(12);
	new_env[0] = ft_strdup("OLDPWD");
	getcwd(current_pwd, sizeof(current_pwd));
	new_env[1] = ft_strjoin("PWD=", current_pwd);
	new_env[2] = ft_strdup("SHLVL=1");
	if (!new_env[0] || !new_env[1] || !new_env[2])
	{
		free_split(new_env);
		exit(12);
	}
	return (new_env);
}

char	**ft_duplicate_env(char **env)
{
	char	**new_env;
	int		i;

	if (!env[0])
		return (set_unset_env());
	new_env = ft_calloc((ft_env_count(env) + 1), sizeof(char *));
	if (!new_env)
		exit(12);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_split(new_env);
			exit(12);
		}
		i++;
	}
	ft_sort_env(&new_env);
	return (new_env);
}
