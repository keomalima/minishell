#include "minishell.h"

static void	ft_print_export(char **env)
{
	int	i;
	int	j;

	j = 0;
	while (env[j])
	{
		printf("export ");
		i = 0;
		while (env[j][i] && env[j][i] != '=')
			printf("%c", env[j][i++]);
		if (env[j][i])
		{
			printf("%c\"", env[j][i++]);
			while (env[j][i])
				printf("%c", env[j][i++]);
			printf("\"");
		}
		printf("\n");
		j++;
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
			return (ft_builtins_exit(ms, NULL, 0));
		if (!ft_modify_env(env_var, ms))
			return (ft_builtins_exit(ms, NULL, 0));
	}
	ft_builtins_exit(ms, env_var, 0);
}
