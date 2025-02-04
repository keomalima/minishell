#include "minishell.h"

size_t	ft_strlen_exp(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_extract_var(char *s, t_ms *ms)
{
	int		len;
	char	*str;
	char	*tmp;

	tmp = ft_strchr(s, '$') + 1;
	while (!ft_isalpha(*tmp))
		tmp = ft_strchr(tmp, '$') + 1;
	len = 0;
	while (tmp[len] && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		exit_handler(ms, 12);
	ft_strlcpy(str, tmp, len + 1);
	return (str);
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
	k = i + ft_strlen_exp(exp.extract) + 1;
	while (exp.env_var && *exp.env_var)
		(*dest)[i++] = *exp.env_var++;
	while (exp.src[k])
		(*dest)[i++] = exp.src[k++];
}
