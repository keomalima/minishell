#include "minishell.h"

static char	*ft_clean_quote_string(char *s, t_expand *expand)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = ft_calloc((ft_strlen(s) - 2 + 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	ft_strlcpy(dest, &s[1], ft_strlen(&s[1]));
	return (dest);
}

char	*ft_handle_quote(char *s, t_expand *expand)
{
	char	*dest;

	if (s && *s && *s == '\"')
		dest = ft_clean_quote_string(s, expand);
	else
	{
		dest = ft_strdup(s);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	return (dest);
}
