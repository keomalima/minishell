#include "minishell.h"

void	ft_print_export(char **env)
{
	while (env && *env)
	{
		printf("export %s\n", *env);
		env++;
	}
}


void	export_command(t_ms *ms, t_cmd *cmd)
{
	t_var	**env_var;

	env_var = NULL;
	if (!cmd->cmd[1])
		ft_print_export(ms->env);
	else
	{

		env_var = ft_get_variable(ms, cmd);
		if (!env_var)
			return;
		ft_print_res_export(env_var);
		
		if (!ft_modify_env(env_var, ms))
			return;
	}
}
