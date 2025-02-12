#include "minishell.h"

int	ft_check_var_spelling(t_var **env_var, t_ms *ms)
{
	int	i;

	i = -1;
	while (env_var[++i])
	{
		if (!ft_is_all_alnum(env_var[i]->name))
		{
			printf("export: '%s': not a valid identifier\n", env_var[i]->name);
			ft_builtins_exit(ms, env_var, 1);
			return (0);
		}
		if (env_var[i]->value && ft_strchr(env_var[i]->value, ';'))
		{
			printf("%s: command not found\n", ft_strchr(env_var[i]->value, ';') + 1);
			ft_builtins_exit(ms, env_var, 127);
			return (0);
		}
	}
	return (1);
}

int	ft_is_valid_export(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (!ft_isalnum(cmd->cmd[i][0]) && cmd->cmd[i][0] != '_')
		{
			printf("export: '%s': not a valid identifier\n", cmd->cmd[i]);
			ft_builtins_exit(ms, NULL, 1);
			return (0);
		}
		if (ft_strchr(cmd->cmd[i], '!'))
		{
			printf("%s: event not found\n", ft_strchr(cmd->cmd[i], '!'));
			ft_builtins_exit(ms, NULL, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_alloc_n_fill(t_var *var, t_var **env_var, t_ms *ms, char *str)
{
	size_t	len;

	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	var->name = ft_calloc((len + 1), sizeof(char));
	if (!var->name)
	{
		ft_builtins_exit(ms, env_var, 12);
		return (0);
	}
	var->value = ft_calloc((ft_strlen(ft_strchr(str, '='))), sizeof(char));
	if (!var->value)
	{
		ft_free(&var->name);
		ft_builtins_exit(ms, env_var, 12);
		return (0);
	}
	ft_strlcpy(var->name, str, (ft_strlen(str) - ft_strlen(ft_strchr(str, '=')) + 1));
	ft_strlcpy(var->value, ft_strchr(str, '=') + 1, ft_strlen(ft_strchr(str, '=')));
	return (1);
}

int	ft_initialize_var(t_var **env_var, t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i + 1])
	{
		env_var[i] = ft_create_new_var(ms, env_var);
		if (!env_var[i])
			return (0);
		if (!ft_strchr(cmd->cmd[i + 1], '='))
		{
			env_var[i]->name = ft_strdup(cmd->cmd[i + 1]);
			if (!env_var[i])
			{
				ft_builtins_exit(ms, env_var, 12);
				return (0);
			}
			env_var[i]->value = NULL;
		}
		else
			if (!ft_export_alloc_n_fill(env_var[i], env_var, ms, cmd->cmd[i + 1]))
				return (0);
		i++;
	}
	return (1);
}

t_var	**ft_get_variable(t_ms *ms, t_cmd *cmd)
{
	t_var	**env_var;

	env_var = NULL;
	if (ft_is_valid_export(ms, cmd))
	{
		env_var = ft_calloc((ft_find_var_count(cmd) + 1), sizeof(t_var *));
		if (!env_var)
		{
			ft_builtins_exit(ms, env_var, 12);
			return (NULL);
		}
		if (!ft_initialize_var(env_var, ms, cmd))
			return (NULL);
		if (!ft_check_var_spelling(env_var, ms))
			return (NULL);
	}
	return (env_var);
}
