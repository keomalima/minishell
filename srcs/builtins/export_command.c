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

size_t	ft_count_arg(char **cmd)
{
	size_t	count;

	if (!cmd || !*cmd || !cmd[1])
		return (0);
	count = 0;
	while (cmd[count + 1])
		count++;
	return (count);
}

int	ft_all_arg_null(char **cmd)
{
	int	i;

	if (!cmd || !*cmd || !cmd[1])
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (*cmd[i])
			return (0);
		i++;
	}
	return (1);
}

void	export_command(t_ms *ms, t_cmd *cmd)
{
	t_var	**env_var;

	env_var = NULL;
	if (!cmd->cmd[1] || (ft_all_arg_null(cmd->cmd)
		&& (ft_count_arg(cmd->cmd) == cmd->nb_expand)))
		ft_print_export(ms->env);
	else
	{
		env_var = ft_get_variable(ms, cmd);
		if (!env_var)
			return ;
		if (!ft_modify_env(env_var, ms, cmd))
			return (ft_builtins_exit(ms, NULL, 0));
	}
	ft_builtins_exit(ms, env_var, 0);
}
