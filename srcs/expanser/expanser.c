#include "../includes/minishell.h"

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
	int		len;
	char	*str;
	char	*tmp;

	tmp = ft_strchr(s, '$') + 1;
	len = 0;
	while (tmp[len] && ft_isalnum(tmp[len]))
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);	////////////////////////////////////////////////////
	ft_strlcpy(str, tmp, len + 1);
	return (str);
}

void	ft_fill_exp(char **dest, t_exp exp)
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
		(*dest)[i++] = *exp.env_var++;
	while (exp.src[j])
		(*dest)[i++] = exp.src[j++];
}

char	*exp_valid_variable(char *s)
{
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s);
	exp.env_var = getenv(exp.extract);
	exp.size = ft_strlen_expanser(s) - ft_strlen_expanser(exp.extract)
		+ ft_strlen_expanser(exp.env_var) - 1;
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

char	*expanser(char *s)
{
	char	*str;

	str = ft_strchr(s, '$') + 1;
	if (ft_isalpha(*str))
		return(exp_valid_variable(s));
	else
		return (s);
}
