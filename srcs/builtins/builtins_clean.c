#include "minishell.h"

static void	clean_var(t_var **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		ft_free(&env_var[i]->name);
		ft_free(&env_var[i]->value);
		free(env_var[i]);
		env_var[i] = NULL;
		i++;
	}
	free(env_var);
	env_var = NULL;
}

void	ft_builtins_exit(t_ms *ms, int exit_code)
{
	errno = 0;
	exit_handler(ms, exit_code);
}

void	ft_builtins_env_exit(t_ms *ms, t_var **env_var, int exit_code)
{
	errno = 0;
	if (env_var)
		clean_var(env_var);
	if (ms->exec->cmd_count > 1)
		exit_handler(ms, exit_code);
	//clean_ms (ms, exit_code);
}