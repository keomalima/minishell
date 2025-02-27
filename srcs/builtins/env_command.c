#include "minishell.h"

void	env_command(t_ms *ms)
{
	int		i;
	size_t	count;

	count = ft_env_count(ms->env);
	i = 0;
	while (ms->env[i])
	{
		printf("%s\n", ms->env[i]);
		i++;
	}
	ft_builtins_exit(ms, NULL, 0);
}
