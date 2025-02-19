#include "minishell.h"

// int	ft_strlen_clear_space(char *s)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (ft_isspace(*s))
// 			s++;
// 		if (*s)
// 		{
// 			count++;
// 			while (*s && !ft_isspace(*s))
// 				s++;
// 		}
// 	}
// 	return (count);
// }

static size_t	ft_strlen_clear_space(char *src)
{
	size_t	i;
	size_t	len;
	size_t	nb_word;

	i = 0;
	len = 0;
	nb_word = 0;
	while (src[i])
	{
		while (src[i] && ft_isspace(src[i]))
			i++;
		if (src[i])
		{
			nb_word++;
			while (src[i] && !ft_isspace(src[i]))
			{
				i++;
				len++;
			}
		}
	}
	if (src[0] && ft_isspace(src[0]))
		len++;
	if (src[i - 1] && ft_isspace(src[i - 1]))
		len++;
	// printf("Last char = {%c}\n", src[i - 1]);
	// printf("len = %zu\n", len);
	// printf("nb_word = %zu\n", nb_word);
	return (len + nb_word - 1);
}

static char	*ft_clear_space(char *src)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen_clear_space(src);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	j = 0;
	i = 0;
	if (ft_isspace(src[0]))
	{
		dest[j] = ' ';
		j++;
	}
	while (src[i])
	{
		while (src[i] && ft_isspace(src[i]))
			i++;
		if (src[i])
			while (src[i] && !ft_isspace(src[i]))
				dest[j++] = src[i++];
		if (src[i] && j < len - 1)
			dest[j++] = ' ';
	}
	if (ft_isspace(src[ft_strlen(src) - 1]))
	{
		dest[j] = ' ';
		j++;
	}
	return (dest);
}

char	*exp_valid_variable(char *s, t_ms *ms, char quote)
{
	char	*extract;
	char	*variable;
	char	*dest;

	extract = s + 1;
	if (!extract)
		return (NULL);
	variable = ft_getenv(ms, extract);
	if (variable == NULL)
		variable = ft_strdup("");
	else if (quote != '\"')
		variable = ft_clear_space(variable);
	else
		variable = ft_strdup(variable);
	if (!variable)
		return (NULL);
	printf("variable = %s\n", variable);
	dest = ft_calloc((ft_strlen(variable) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, variable, (ft_strlen(variable) + 1));
	ft_free(&s);
	ft_free(&variable);
	return (dest);
}
