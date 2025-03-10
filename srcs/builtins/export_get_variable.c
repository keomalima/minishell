#include "minishell.h"

static int	ft_valid_syntax(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (ft_strchr(cmd->cmd[i], '!'))
		{
			ft_print_error(ft_strchr(cmd->cmd[i], '!'),
				": event not found\n", NULL);
			ft_builtins_exit(ms, NULL, 2);
			ms->exit_status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_export_fill(t_var *var, t_var **env_var, t_ms *ms, char *str)
{
	size_t	len;

	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	var->name = ft_calloc((len + 1), sizeof(char));
	if (!var->name)
	{
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	var->value = ft_calloc((ft_strlen(ft_strchr(str, '='))), sizeof(char));
	if (!var->value)
	{
		ft_free(&var->name);
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	ft_strlcpy(var->name, str,
		(ft_strlen(str) - ft_strlen(ft_strchr(str, '=')) + 1));
	ft_strlcpy(var->value, ft_strchr(str, '=') + 1,
		ft_strlen(ft_strchr(str, '=')));
	return (1);
}

static int	ft_initialize_var(t_var **env_var, t_ms *ms, t_cmd *cmd)
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
			if (!env_var[i]->name)
			{
				ft_builtins_exit(ms, env_var, 12);
				exit (12);
			}
		}
		else
			if (!ft_export_fill(env_var[i], env_var, ms, cmd->cmd[i + 1]))
				return (0);
		i++;
	}
	return (1);
}

t_var	**ft_get_variable(t_ms *ms, t_cmd *cmd)
{
	t_var	**env_var;

	env_var = NULL;
	if (ft_valid_syntax(ms, cmd))
	{
		env_var = ft_calloc((ft_find_var_count(cmd) + 1), sizeof(t_var *));
		if (!env_var)
		{
			ft_builtins_exit(ms, env_var, 12);
			exit (12);
		}
		if (!ft_initialize_var(env_var, ms, cmd))
		{
			ft_builtins_exit(ms, env_var, 12);
			exit (12);
		}
	}
	return (env_var);
}
