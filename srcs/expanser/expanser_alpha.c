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

size_t	ft_strlen_between_space(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

t_list	*ft_clear_space(char *s)
{
	t_list	*clean;
	char	*str;
	int		i;

	if (!s)
		return (ft_lstnew(NULL));
	clean = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			str = ft_calloc((ft_strlen_between_space(&s[i]) + 1), sizeof(char));
			if (!str)
				return (NULL);		//////////
			ft_strlcpy(str, &s[i], (ft_strlen_between_space(&s[i]) + 1));
			// printf("str clear space [%s]\n", str);
			ft_lstadd_back(&clean, ft_lstnew(str));
			i += ft_strlen_between_space(&s[i]);
		}
	}
	return (clean);
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

