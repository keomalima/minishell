#include "minishell.h"

char	*ft_extract_var(char *s)
{
	int		len;
	char	*str;
	char	*tmp;

	tmp = ft_strchr(s, '$') + 1;
	len = 0;
	while (tmp[len] && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, tmp, len + 1);
	return (str);
}

char	*ft_clear_space(char *src)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!src)
		return (NULL);
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
		while (src[i] && src[i] != ' ')
		{
			i++;
			len++;
		}
	}
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	len = 0;
	i = 0;
	while (src[i])
	{
		if (src[i] == ' ')
			dest[len++] = src[i++];
		while (src[i] && src[i] == ' ')
			i++;
		while (src[i] && src[i] != ' ')
			dest[len++] = src[i++];
	}
	// ft_free(&src);
	return (dest);
}

void	ft_fill_exp(char **dest, t_exp exp)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	while (exp.src[j])
	{
		if (exp.src[j] == '$' && ft_isalpha(exp.src[j + 1]))
			break ;
		j++;
	}
	i = 0;
	while (i < j)
	{
		(*dest)[i] = exp.src[i];
		i++;
	}
	k = i + ft_strlen(exp.extract) + 1;
	while (exp.env_var && *exp.env_var)
		(*dest)[i++] = *exp.env_var++;
	while (exp.src[k])
		(*dest)[i++] = exp.src[k++];
}
