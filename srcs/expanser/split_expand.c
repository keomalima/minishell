#include "minishell.h"

static size_t	ft_strlen_expand(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '$')
	{
		i++;
		if (s[i] && ft_isquote(s[i]))
		{
			ft_skip_quote(s, &i);
			return (i);
		}
		else if (s[i] == '?')
			i++;
		else
		{
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			return (i);
		}
	}
	else
		while (s[i] && s[i] != '$')
			i++;
	return (i);
}

char	*ft_split_expand(char *s, int *j, t_expand *expand)
{
	char	*str;
	size_t	len;

	if (s[*j] == '\0') //check if its chorrect
		len = 0;
	else
		len = ft_strlen_expand(&s[*j]);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		ft_clear_expand(expand, 12);
	ft_strlcpy(str, &s[*j], (len + 1));
	*j = *j + len - 1;
	return (str);
}
