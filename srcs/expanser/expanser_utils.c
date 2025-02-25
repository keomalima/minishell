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
void	ft_clear_expand(t_expand *expand, int exit_code)
{
	if (expand->initial_list)
		ft_lstclear(&expand->initial_list, &del_content);
	if (expand->exp_list)
		ft_lstclear(&expand->exp_list, &del_content);
	exit_handler(expand->ms, exit_code);
}