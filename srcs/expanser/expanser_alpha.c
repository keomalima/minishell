#include "minishell.h"

int	ft_contains_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			return (1);
		i++;
	}
	return (0);
}



char	*exp_valid_variable(char *s, t_ms *ms)
{
	char	*variable;
	char	*dest;

	if (!s)
		return (NULL);
	variable = ft_getenv(ms, s);
	// printf("extract = %s	|	variable = %s\n", s, variable);

	if (variable == NULL)
		dest = NULL;
	else
		dest = ft_strdup(variable);

	// printf("exp valid [%s]\n", dest);
	return (dest);
}

