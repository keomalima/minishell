#include "minishell.h"

int	ft_find_var(char *path, t_ms *ms)
{
	int		i;
	int		comp;

	i = 0;
	while (ms->env[i])
	{
		comp = ft_strncmp(ms->env[i], path, ft_strlen(path));
		if (comp == 0)
			return (i);
		i++;
	}
	return (-1);
}
