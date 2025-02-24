#include "minishell.h"

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
