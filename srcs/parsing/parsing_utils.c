#include "../includes/minishell.h"

void	*ft_free(char **data)
{
	if (*data)
		free(*data);
	*data = NULL;
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (0);
	else
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int ft_isspaces(char c)
{
	if (c == 32 || c == '\f' || c == '\n' || c== '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}
