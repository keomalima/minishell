#include "../includes/minishell.h"

int ft_is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
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

void	*ft_free(char **data)
{
	if (*data)
		free(*data);
	*data = NULL;
	return (NULL);
}

char *ft_clean_quote(char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	quote;
	char	*ret;

	if (!ft_strchr(s, 39) && !ft_strchr(s, 34))
		return (s);
	i = 0;
	while (s[i] && !ft_is_quote(s[i]))
		i++;
	quote = s[i];
	if (!ft_strchr(&s[i + 1], quote))
		return (s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != quote)
			len++;
		i++;
	}
	ret = ft_calloc((len + 1), sizeof(char));
	if (!ret)
		return (ft_free(&s));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != quote)
		{
			ret[j] = s[i];
			j++;
		}
		i++;
	}
	ft_free(&s);
	return (ret);
}
