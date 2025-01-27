#include "../includes/minishell.h"

t_type	ft_define_state(char c)
{
	if (c == 34)
		return (IN_DOUBLE_QUOTE);
	if (c == 39)
		return (IN_SINGLE_QUOTE);
	else
		return (START);
}

size_t ft_strlen_state(char *s, t_type state)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (ft_define_state(s[i]) != state)
			len++;
		i++;
	}
	return (len);
}

char *ft_strndup_ms(char *s, t_type state)
{
	int		len;
	char	*str;
	size_t	i;
	size_t	j;

	len = ft_strlen_state(s, state);
	str = ft_calloc((len +1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_define_state(s[i]) != state)
			str[j++] = s[i];
		i++;
	}
	return (str);
}
