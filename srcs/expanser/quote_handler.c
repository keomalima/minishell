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

void	ft_reset_quote(char *s, t_exp_utils *util, t_expand *expand)
{
	char	*joined;
	char	*str;

	if (s && *s && *s == '\"')
	{
		joined = ft_joined_list(util, expand);
		str = ft_calloc((ft_strlen(joined) + 3), sizeof(char));
		if (!str)
		{
			ft_free(&joined);
			ft_lstclear(&util->new_list);
			ft_clear_expand(expand, 12);
		}
		str[0] = '\"';
		ft_strlcpy(&str[1], joined, (ft_strlen(joined) + 1));
		str[ft_strlen(str)] = '\"';
		ft_lstclear(&util->new_list);
		util->new_list = ft_lstnew(str);
		if (!util->new_list)
		{
			ft_free(&joined);
			ft_expand_alloc_failure(expand, util, str);
		}
		ft_free(&joined);
	}
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
