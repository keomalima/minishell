#include "minishell.h"


size_t	ft_find_var_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd->cmd[count])
	{
		count++;
	}
	return (count - 1);
}

int	ft_is_all_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


void	clean_var(t_var **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		ft_free(&env_var[i]->name);
		ft_free(&env_var[i]->value);
		free(env_var[i]);
		env_var[i] = NULL;
		i++;
	}
	free(env_var);
	env_var = NULL;
}

t_var	*ft_create_new_var(t_ms *ms, t_var **env_var)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
	{
		export_exit_o_return(ms, env_var, 12);
		return (NULL);
	}
	new->name = NULL;
	new->value = NULL;
	return (new);
}

void	export_exit_o_return(t_ms *ms, t_var **env_var, int exit_code)
{
	if (env_var)
		clean_var(env_var);
	if (ms->cmd_count > 1)
		exit_handler(ms, exit_code);
	clean_ms (ms, exit_code);
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

char	**ft_duplicate_env(t_var **env_var, t_ms *ms)
{
	char	**new_env;
	int		i;

	if (ms->mod_env == 1)
		return (NULL);
	new_env = ft_calloc((ft_env_count(ms->env) + 1), sizeof(char *));
	if (!new_env)
	{
		export_exit_o_return(ms, env_var, 12);
		return (NULL);
	}
	i = 0;
	while (ms->env[i])
	{
		new_env[i] = ft_strdup(ms->env[i]);
		if (!new_env[i])
		{
			export_exit_o_return(ms, env_var, 12);
			return (NULL);
		}
		i++;
	}
	ms->mod_env = 1;
	return (new_env);
}

