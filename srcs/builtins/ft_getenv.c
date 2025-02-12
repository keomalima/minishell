#include "minishell.h"

char	*ft_getenv(t_ms *ms, char *str)
{
	int	i;

	if (!ms || !ms->env)
		return (NULL);
	i = 0;
	while (ms->env[i])
	{
		if (ft_strncmp(ms->env[i], str, ft_strlen(str)) == 0 && ms->env[i][ft_strlen(str) + 1] == '=')
			return (ms->env[i]);
		i++;
	}
	return (NULL);
}
