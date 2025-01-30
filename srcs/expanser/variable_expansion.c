#include "minishell.h"

size_t	ft_strlen_expanser(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_extract_var(char *s)
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
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);	////////////////////////////////////////////////////
	len = 0;
	while (s[i] && ft_isalnum(s[i]))
		str[len++] = s[i++];
	return (str);
}

void ft_fill_exp(char **dest, t_exp exp)
{
	int		i;
	int		j;

	i = 0;
	while (exp.src[i] && exp.src[i] != '$')
	{
		(*dest)[i] = exp.src[i];
		i++;
	}
	j = i + ft_strlen_expanser(exp.extract) + 1;
	while (exp.env_var && *exp.env_var)
	{
		(*dest)[i] = *exp.env_var;
		i++;
		exp.env_var++;
	}
	while (exp.src[j])
	{
		(*dest)[i] = exp.src[j];
		i++;
		j++;
	}
}

char *expanse_var(char *s)
{
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s);
	printf("extract = [%s]\n", exp.extract);
	exp.env_var = getenv(exp.extract);
	printf("var = [%s]\n", exp.env_var);
	exp.size = ft_strlen_expanser(s) - ft_strlen_expanser(exp.extract) + ft_strlen_expanser(exp.env_var) - 1;
	printf("size = %zu\n", exp.size);
	dest = ft_calloc((exp.size + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&exp.extract);
		ft_free(&exp.env_var);
		return (NULL);	///////////////////////////////////////////////////////
	}
	ft_fill_exp(&dest, exp);
	ft_free(&exp.src);
	ft_free(&exp.extract);
	return (dest);
}