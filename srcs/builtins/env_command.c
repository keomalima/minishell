#include "minishell.h"

void	env_command(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i])
	{
		printf("%s\n", ms->env[i]);
		i++;
	}
	ft_builtins_env_exit(ms, NULL, 0);
}
