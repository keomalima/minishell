#include "minishell.h"

size_t	ft_count_word_exp(char *s, size_t *count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (ft_isquote(s[i]))
				ft_skip_quote(s, &i);
			else if (s[i] == '?')
				i++;
			else
			{
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					i++;
			}
		}
		else
			while (s[i] && s[i] != '$')
				i++;
		(*count)++;
	}
	return (*count);
}

size_t	ft_count_exp(char *s)
{
	char	*tmp;
	size_t	count_exp;

	count_exp = 0;
	tmp = ft_strchr(s, '$');
	while (tmp)
	{
		if (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?'
			|| ft_isquote(*(tmp + 1)))
			count_exp++;
		tmp = ft_strchr((tmp + 1), '$');
	}
	return (count_exp);
}
