#include "minishell.h"

static size_t	ft_strlen_clear_space(char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (src[i])
	{
		if (src[i] == ' ')
		{
			i++;
			len++;
		}
		while (src[i] && src[i] == ' ')
			i++;
		// if (src[i] != 0)
		// 	len++;
		while (src[i] && src[i] != ' ')
		{
			i++;
			len++;
		}
	}
	// printf("len = %zu\n", len);
	return (len);
}

static char	*ft_clear_space(char *src)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!src)
		return (NULL);
	dest = ft_calloc((ft_strlen_clear_space(src) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	j = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] == ' ')
			dest[j++] = src[i++];
		while (src[i] && src[i] == ' ')
			i++;
		while (src[i] && src[i] != ' ')
			dest[j++] = src[i++];
	}
	return (dest);
}

char	*exp_valid_variable(char *s, t_ms *ms)
{
	char	*extract;
	char	*variable;
	char	*dest;

	extract = s + 1;
	if (!extract)
		return (NULL);
	variable = ft_getenv(ms, extract);
	variable = ft_clear_space(variable);
	// dest = ft_strdup(variable);
	dest = ft_calloc((ft_strlen(variable) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, variable, (ft_strlen(variable) + 1));
	ft_free(&s);
	ft_free(&variable);
	return (dest);
}
