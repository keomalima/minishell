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
		exit (12);
	}
	ft_strlcpy(dest, cur_var->name, (ft_strlen(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy(&dest[ft_strlen(dest)], "=", 2);
	ft_strlcpy(&dest[ft_strlen(dest)],
		cur_var->value, (ft_strlen(cur_var->value) + 1));
	ft_free(&ms->env[i]);
	return (dest);
}

static char	*ft_set_new_variable(t_var *cur_var, t_var **env_var, t_ms *ms, char **new_env)
{
	size_t	len;
	char	*new_var;

	len = ft_strlen(cur_var->name) + ft_strlen(cur_var->value);
	if (cur_var->value)
		len++;
	new_var = ft_calloc((len + 1), sizeof(char));
	if (!new_var)
	{
		free(new_env);
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	ft_strlcpy(new_var, cur_var->name, (ft_strlen(cur_var->name) + 1));
	if (cur_var->value)
		ft_strlcpy(&new_var[ft_strlen(new_var)], "=", 2);
	ft_strlcpy(&new_var[ft_strlen(new_var)],
		cur_var->value, (ft_strlen(cur_var->value) + 1));
	return (new_var);
}

static char	**ft_add_var_to_env(t_var *current_var, t_var **env_var, t_ms *ms)
{
	size_t	i;
	size_t	j;
	char	**new_env;

	new_env = ft_calloc((ft_env_count(ms->env) + 2), sizeof(char *));
	if (!new_env)
	{
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	i = 0;
	j = 0;
	while (ms->env[i] && ft_strcmp(ms->env[i], current_var->name) < 0)
		new_env[j++] = ms->env[i++];
	new_env[j++] = ft_set_new_variable(current_var, env_var, ms, new_env);
	if (!new_env[j - 1])
	{
		free_split(new_env);
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	while (ms->env[i])
		new_env[j++] = ms->env[i++];
	free(ms->env);
	return (new_env);
}

static int	ft_valid_variable(t_ms *ms, t_var *env_var, char *arg, t_cmd *cmd)
{
	if (!*env_var->name && (ft_count_arg(cmd->cmd) - cmd->nb_expand > 0))
	{
		ft_print_error("export: \'", arg, "\': not a valid identifier\n");
		cmd->nb_expand += 1;
		ms->exit_status = 1;
		return (0);
	}
	else if ((*env_var->name && !ft_is_all_alnum(env_var->name))
		|| (*env_var->name
			&& !ft_isalpha(env_var->name[0]) && env_var->name[0] != '_'))
	{
		ft_print_error("export: \'", arg, "\': not a valid identifier\n");
		ms->exit_status = 1;
		return (0);
	}
	return (1);
}

int	ft_modify_env(t_var **env_var, t_ms *ms, t_cmd *cmd)
{
	int		i;
	int		index;

	if (!ms->env)
		return (1);
	i = -1;
	while (env_var[++i])
	{
		if (!ft_valid_variable(ms, env_var[i], cmd->cmd[i + 1], cmd))
			continue ;
		index = ft_find_var(env_var[i]->name, ms);
		if (index >= 0 && env_var[i]->value)
		{
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
