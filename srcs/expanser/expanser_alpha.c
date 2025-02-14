#include "minishell.h"

static char	*ft_extract_var(char *s)
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
		while (src[i] && src[i] != ' ')
		{
			i++;
			len++;
		}
	}
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
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s);
	if (!exp.extract)
		return (NULL);
	exp.env_var = ft_getenv(ms, exp.extract);
	exp.env_var = ft_clear_space(exp.env_var);
	exp.size = ft_strlen(s) - ft_strlen(exp.extract)
		+ ft_strlen(exp.env_var) - 1;
	dest = ft_calloc((exp.size + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&exp.env_var);
		ft_free(&exp.extract);
		return (NULL);
	}
	ft_strlcpy(dest, exp.env_var, (ft_strlen(exp.env_var) + 1));
	ft_free(&s);
	ft_free(&exp.extract);
	ft_free(&exp.env_var);
	return (dest);
}
