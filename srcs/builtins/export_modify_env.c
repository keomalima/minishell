#include "minishell.h"

char	*ft_remplace_value(t_var *cur_var, t_var **env_var, t_ms *ms, int index)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_ms(cur_var->name) + ft_strlen_ms(cur_var->value);
	if (cur_var->value)
		len++;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	ft_strlcpy_ms(dest, cur_var->name, (ft_strlen_ms(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy_ms(&dest[ft_strlen_ms(dest)], "=", 2);
	ft_strlcpy_ms(&dest[ft_strlen_ms(dest)],
		cur_var->value, (ft_strlen_ms(cur_var->value) + 1));
	ft_free(&ms->env[index]);
	return (dest);
}

char	*ft_set_new_variable(t_var *cur_var, t_var **env_var, t_ms *ms)
{
	size_t	len;
	char	*new_var;

	len = ft_strlen_ms(cur_var->name) + ft_strlen_ms(cur_var->value);
	if (cur_var->value)
		len++;
	new_var = ft_calloc((len + 1), sizeof(char));
	if (!new_var)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (NULL);
	}
	ft_strlcpy_ms(new_var, cur_var->name, (ft_strlen_ms(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy_ms(&new_var[ft_strlen_ms(new_var)], "=", 2);
	ft_strlcpy_ms(&new_var[ft_strlen_ms(new_var)],
		cur_var->value, (ft_strlen_ms(cur_var->value) + 1));
	free(ms->env);
	return (new_var);
}

char	**ft_add_var_to_env(t_var *current_var, t_var **env_var, t_ms *ms)
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
	while (ms->env[i])
	{
		new_env[i] = ms->env[i];
		i++;
	}
	new_env[i] = ft_set_new_variable(current_var, env_var, ms);
	if (!new_env[i])
		return (NULL);
	return (new_env);
}

int	ft_modify_env(t_var **env_var, t_ms *ms)
{
	int		i;
	int		index;

	ms->env = ft_duplicate_env(env_var, ms);
	if (!ms->env)
		return (1);
	i = -1;
	while (env_var[++i])
	{
		index = ft_find_var(env_var[i]->name, ms);
		if (index >= 0 && env_var[i]->value)		// Variable found
		{
			index = ft_find_var(env_var[i]->name, ms);
			ms->env[index] = ft_remplace_value(env_var[i], env_var, ms, index);
			if (!ms->env[index])
				return (0);
		}
		else if (index == -1)				// Variable not found
		{
			ms->env = ft_add_var_to_env(env_var[i], env_var, ms);
			if (!ms->env)
				return (0);
		}
	}
	return (1);
}
