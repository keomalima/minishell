#include "minishell.h"

size_t	ft_find_var_count(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd->cmd[count])
	{
		count++;
	}
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

t_var	*ft_create_new_var(t_ms *ms, t_var **env_var)
{
	t_var	*new;

	new = NULL; //malloc(sizeof(t_var));
	if (!new)
	{
		ft_builtins_exit(ms, env_var, 12);
		exit (12);
	}
	new->name = NULL;
	new->value = NULL;
	return (new);
}
