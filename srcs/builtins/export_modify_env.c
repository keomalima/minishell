#include "minishell.h"

int	ft_find_var(t_var *env_var, t_ms *ms)
{
	int		i;
	int		comp;

	i = 0;
	while (ms->env[i])
	{
		comp = ft_strncmp(ms->env[i], env_var->name, ft_strlen_exp(env_var->name));
		if (comp == 0 && ms->env[i][ft_strlen_exp(env_var->name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_duplicate_env(t_var **env_var, t_ms *ms)
{
	char	**new_env;
	int		i;

	i = 0;
	while (ms->env[i])
		i++;
	new_env = ft_calloc((i + 1), sizeof(char *));
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



char	*ft_remplace_value(char *src, t_var *current_var, t_var **env_var, t_ms *ms)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_exp(current_var->name) + ft_strlen_exp(current_var->value) + 1;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		export_exit_o_return(ms, env_var, 12);
		return (NULL);
	}
	ft_strlcpy(dest, current_var->name, (ft_strlen_exp(current_var->name) + 1));
	ft_strlcpy(&dest[ft_strlen_exp(dest)], "=", 2);
	ft_strlcpy(&dest[ft_strlen_exp(dest)], current_var->value, (ft_strlen_exp(current_var->value) + 1));
	printf("dest [%s]\n", dest);
	ft_free(&src);
	(void)src;
	return (dest);

}

int	ft_modify_env(t_var **env_var, t_ms *ms)
{
	int		i;
	int		index;
	size_t	env_size;

	i = 0;
	index = ft_find_var(env_var[i], ms);
	if (index >= 0)
	{
		printf("Replacement of existing environnement variable\n");
		if (ms->mod_env == 0)
		{
			ms->env = ft_duplicate_env(env_var, ms);
			if (!ms->env)
				return (1);
		}
		index = ft_find_var(env_var[i], ms);
		ms->env[index] = ft_remplace_value(ms->env[index], env_var[i], env_var, ms);
		printf("My variable : %s\n", ms->env[index]);

	}
	else
	{
		printf("Adding of a new variable\n");
		if (ms->mod_env == 0)
		{
			ms->env = ft_duplicate_env(env_var, ms);
			if (!ms->env)
				return (1);
		}
		env_size = 0;
		while (ms->env[env_size])
			env_size++;
		env_var[i]->new_env = ft_calloc((env_size + 2), sizeof(char *));
		if (!env_var[i]->new_env)
		{
			export_exit_o_return(ms, env_var, 12);
			return (1);
		}
		env_size = 0;
		while (ms->env[env_size])
		{
			env_var[i]->new_env[env_size] = ms->env[env_size];
			env_size++;
		}
		printf("Last env : %s\n", env_var[i]->new_env[env_size-1]);

		ft_strlcpy(env_var[i]->new_env[env_size], env_var[i]->name, (ft_strlen_exp(env_var[i]->name) + 1));
		printf("My variable ?? : %s\n", env_var[i]->new_env[env_size]);
		ft_strlcpy(&env_var[i]->new_env[env_size][ft_strlen_exp(env_var[i]->new_env[env_size])], "=", 2);
		ft_strlcpy(&env_var[i]->new_env[env_size][ft_strlen_exp(env_var[i]->new_env[env_size])], env_var[i]->value, (ft_strlen_exp(env_var[i]->value) + 1));
		free(ms->env);
		ms->env = env_var[i]->new_env;
		printf("My variable : %s\n", ms->env[env_size]);
	}
	// ft_print_export(ms->env);
	return (1);
}
