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
			export_exit_o_return(ms, env_var, 1);;
			return (0);
		}
		if (env_var[i]->value && ft_strchr(env_var[i]->value, ';'))
		{
			printf("%s: command not found\n", ft_strchr(env_var[i]->value, ';') + 1);
			export_exit_o_return(ms, env_var, 127);
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
			export_exit_o_return(ms, NULL, 1);
			return (0);
		}
		if (ft_strchr(cmd->cmd[i], '!'))
		{
			printf("%s: event not found\n", ft_strchr(cmd->cmd[i], '!'));
			export_exit_o_return(ms, NULL, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_alloc_n_fill_name_value(t_var *var, t_var **env_var, t_ms *ms, char *str)
{
	var->name = ft_calloc((ft_strlen_exp(str) - ft_strlen_exp(ft_strchr(str, '=')) + 1), sizeof(char));
	if (!var->name)
	{
		export_exit_o_return(ms, env_var, 12);
		return (0);
	}
	var->value = ft_calloc((ft_strlen_exp(ft_strchr(str, '=')) + 2), sizeof(char));
	if (!var->value)
	{
		ft_free(&var->name);
		export_exit_o_return(ms, env_var, 12);
		return (0);
	}
	ft_strlcpy(var->name, str, (ft_strlen_exp(str) - ft_strlen_exp(ft_strchr(str, '=')) + 1));
	var->value[0] = '\"';
	ft_strlcpy((var->value + 1), ft_strchr(str, '=')+1, ft_strlen_exp(ft_strchr(str, '=')));
	var->value[ft_strlen_exp(var->value)] = '\"';
	return (1);
}

int	ft_initialize_var(t_var **env_var, t_ms *ms, t_cmd *cmd)
{
	int i;


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
				export_exit_o_return(ms, env_var, 12);
				return (0);
			}
			env_var[i]->value = NULL;
		}
		else
			if (!ft_alloc_n_fill_name_value(env_var[i], env_var, ms, cmd->cmd[i + 1]))
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
			if (ms->cmd_count > 1)
				exit_handler(ms, 12);
			clean_ms (ms, 12);
			return (NULL);
		}

		if (!ft_initialize_var(env_var, ms, cmd))
			return (NULL);
		if (!ft_check_var_spelling(env_var, ms))
			return (NULL);
	}
	return (env_var);
}
