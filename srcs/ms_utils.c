#include "minishell.h"

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

char	*ft_getenv(t_ms *ms, char *str)
{
	int	i;

	if (!ms || !ms->env)
		return (NULL);
	i = 0;
	while (ms->env[i])
	{
		if (ft_strncmp(ms->env[i], str, ft_strlen(str)) == 0
			&& ms->env[i][ft_strlen(str)] == '=')
			return (&ms->env[i][ft_strlen(str) + 1]);
		i++;
	}
	return (NULL);
}

int	ft_is_special_cmd(char *big, char *little)
{
	size_t	i;

	i = 0;
	while (big[i] && big[i] == ' ')
		i++;
	if (ft_strncmp(&big[i], little, ft_strlen(little)) == 0
		&& ((&big[i])[ft_strlen(little)] == ' '
		|| (&big[i])[ft_strlen(little)] == 0))
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
