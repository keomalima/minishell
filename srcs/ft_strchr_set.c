#include "../includes/minishell.h"

int	ft_is_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while(set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char *ft_strchr_set(char *s, char *set)
{
	while (*s)
	{
		if (ft_is_set(*s, set))
			return ((char *)s);
		s++;
	}
	return (NULL);
}
