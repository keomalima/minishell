#include "minishell.h"

void	env_command(t_ms *ms, t_cmd *cmd)
{
	int		i;

	if (cmd->cmd[1])
	{
		ft_print_error("Too many arguments\n", NULL, NULL);
		ms->exit_status = 1;
		ft_builtins_exit(ms, NULL, 1);
		return ;
	}
	i = 0;
	while (ms->env[i])
	{
		if (ft_strchr(ms->env[i], '='))
			printf("%s\n", ms->env[i]);
		i++;
	}
	ft_builtins_exit(ms, NULL, 0);
}
