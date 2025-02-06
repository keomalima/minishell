#include "minishell.h"


size_t	ft_find_var_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd->cmd[count])
	{
		count++;
	}
	printf("count = %zu\n", count - 1);
	return (count - 1);
}

int	ft_is_all_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


void	clean_var(t_var **env_var)
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

t_var	*ft_create_new_var(t_ms *ms, t_var **env_var)
{
	t_var	*new;

	new = malloc(sizeof(t_var));
	if (!new)
	{
		export_exit_o_return(ms, env_var, 12);
		return (NULL);
	}
	new->name = NULL;
	new->new_env = NULL;
	new->value = NULL;
	return (new);
}

void	export_exit_o_return(t_ms *ms, t_var **env_var, int exit_code)
{
	if (env_var)
		clean_var(env_var);
	if (ms->cmd_count > 1)
		exit_handler(ms, exit_code);
	clean_ms (ms, exit_code);
}
