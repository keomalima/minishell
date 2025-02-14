#include "minishell.h"

static char	*ft_remplace_value(t_var *cur_var, t_var **env_var, t_ms *ms, int i)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(cur_var->name) + ft_strlen(cur_var->value);
	if (cur_var->value)
		len++;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	ft_strlcpy(dest, cur_var->name, (ft_strlen(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy(&dest[ft_strlen(dest)], "=", 2);
	ft_strlcpy(&dest[ft_strlen(dest)],
		cur_var->value, (ft_strlen(cur_var->value) + 1));
	ft_free(&ms->env[i]);
	return (dest);
}

static char	*ft_set_new_variable(t_var *cur_var, t_var **env_var, t_ms *ms)
{
	size_t	len;
	char	*new_var;

	len = ft_strlen(cur_var->name) + ft_strlen(cur_var->value);
	if (cur_var->value)
		len++;
	new_var = ft_calloc((len + 1), sizeof(char));
	if (!new_var)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	ft_strlcpy(new_var, cur_var->name, (ft_strlen(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy(&new_var[ft_strlen(new_var)], "=", 2);
	ft_strlcpy(&new_var[ft_strlen(new_var)],
		cur_var->value, (ft_strlen(cur_var->value) + 1));
	return (new_var);
}

static void	ft_copy_env(char **n_env, char **o_env, size_t i_new, size_t *i_old)
{
	n_env[i_new] = o_env[*i_old];
	i_new++;
	(*i_old)++;
}

static char	**ft_add_var_to_env(t_var *current_var, t_var **env_var, t_ms *ms)
{
	size_t	i;
	char	**new_env;

	new_env = ft_calloc((ft_env_count(ms->env) + 2), sizeof(char *));
	if (!new_env)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	i = 0;
	while (ms->env[i] && ft_strcmp(current_var->name, ms->env[i]) > 0)
		ft_copy_env(new_env, ms->env, i, &i);
	new_env[i] = ft_set_new_variable(current_var, env_var, ms);
	if (!new_env[i])
	{
		free_split(new_env);
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	while (ms->env[i])
		ft_copy_env(new_env, ms->env, i + 1, &i);
	free(ms->env);
	ms->env = NULL;
	return (new_env);
}

int	ft_modify_env(t_var **env_var, t_ms *ms)
{
	int		i;
	int		index;

	if (!ms->env)
		return (1);
	i = -1;
	while (env_var[++i])
	{
		index = ft_find_var(env_var[i]->name, ms);
		if (index >= 0 && env_var[i]->value)
		{
			index = ft_find_var(env_var[i]->name, ms);
			ms->env[index] = ft_remplace_value(env_var[i], env_var, ms, index);
			if (!ms->env[index])
				return (0);
		}
		else if (index == -1)
		{
			ms->env = ft_add_var_to_env(env_var[i], env_var, ms);
			if (!ms->env)
				return (0);
		}
	}
	return (1);
}
