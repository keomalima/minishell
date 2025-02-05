#include "minishell.h"

void	ft_print_export(char **env)
{
	while (*env)
	{
		printf("export %s\n", *env);
		env++;
	}
}

void	ft_initialize_var(t_var *env_var, t_ms *ms, t_cmd *cmd)
{
	if (!cmd->cmd[1] || !*cmd->cmd[1])
	{
		printf("export: '': not a valid identifier\n");
		if (ms->cmd_count > 1)
			exit_handler(ms, 1);
		return ;				///// have to free before return ??
	}
	else if (!ft_strchr(cmd->cmd[1], '='))
	{
		env_var->var_name = cmd->cmd[1];
		env_var->var_value = NULL;
	}
	else
	{
		env_var->var_name = ft_calloc((ft_strlen_exp(cmd->cmd[1]) - ft_strlen_exp(ft_strchr(cmd->cmd[1], '=')) + 1), sizeof(char));
		env_var->var_value = ft_calloc(ft_strlen_exp(ft_strchr(cmd->cmd[1], '=')), sizeof(char));
		if ((!env_var->var_name || !env_var->var_value) && ms->cmd_count > 1)
			exit_handler(ms, 1);
		if (!env_var->var_name || !env_var->var_value)
			return ;				///// have to free before return ??
		ft_strlcpy(env_var->var_name, cmd->cmd[1], (ft_strlen_exp(cmd->cmd[1]) - ft_strlen_exp(ft_strchr(cmd->cmd[1], '=')) + 1));
		ft_strlcpy(env_var->var_value, ft_strchr(cmd->cmd[1], '=')+1, ft_strlen_exp(ft_strchr(cmd->cmd[1], '=')));
	}
}

void	ft_set_env(t_ms *ms, t_cmd *cmd)
{
	t_var	env_var;

	ft_initialize_var(&env_var, ms, cmd);
	printf("variable name = [%s]\n", env_var.var_name);
	printf("variable value = [%s]\n", env_var.var_value);
}

void	export_command(t_ms *ms, t_cmd *cmd)
{
	if (!cmd->cmd[1])
		ft_print_export(ms->env);
	else
		ft_set_env(ms, cmd);
}