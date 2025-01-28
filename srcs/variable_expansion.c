#include "../includes/minishell.h"

char	*ft_extract_var(char *s, size_t *size)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] && s[i] == '$')
		i++;
	len = i;
	while (s[len] && ft_isalnum(s[len]))
		len++;
	len = len - i;
	*size = ft_strlen(s) - len - 1;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);	////////////////////////////////////////////////////
	len = 0;
	while (s[i] && ft_isalnum(s[i]))
	{
		str[len] = s[i];
		len++;
		i++;
	}
	return (str);
}

char *get_var(char *s)
{
	char	*extract;
	char	*var;
	char	*ret;
	size_t	size;
	int		i;
	int		j;

	extract = ft_extract_var(s, &size);
	var = getenv(extract);
	size = size + ft_strlen(var);
	ret = ft_calloc((size + 1), sizeof(char));
	if (!ret)
	{
		ft_free(&extract);
		ft_free(&var);
		return (NULL);	///////////////////////////////////////////////////////
	}
	i = 0;
	while (s[i] && s[i] != '$')
	{
		ret[i] = s[i];
		i++;
	}
	j = i + ft_strlen(extract) + 1;
	while (*var)
	{
		ret[i] = *var;
		i++;
		var++;
	}
	while (s[j])
	{
		ret[i] = s[j];
		i++;
		j++;
	}
	ft_free(&extract);
	ft_free(&s);
	return (ret);
}
