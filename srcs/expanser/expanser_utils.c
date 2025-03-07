#include "minishell.h"

size_t	ft_count_alpha_exp(char *s)
{
	char	*tmp;
	size_t	count_exp;

	count_exp = 0;
	tmp = ft_strchr(s, '$');
	while (tmp)
	{
		if ((tmp + 1) && ft_isalpha(*(tmp + 1)))
			count_exp++;
		tmp = ft_strchr((tmp + 1), '$');
	}
	return (count_exp);
}

size_t	ft_count_exp(char *s)
{
	char	*tmp;
	size_t	count_exp;

	count_exp = 0;
	tmp = ft_strchr(s, '$');
	while (tmp)
	{
		if ((tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?'
				|| ft_isquote(*(tmp + 1))))
			count_exp++;
		tmp = ft_strchr((tmp + 1), '$');
	}
	return (count_exp);
}

void	ft_clear_expand(t_expand *expand, int exit_code)
{
	if (expand->initial_list)
		ft_lstclear(&expand->initial_list);
	if (expand->exp_list)
		ft_lstclear(&expand->exp_list);
	exit_handler(expand->ms, exit_code);
}

void	ft_skip_quote(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
}

int	ft_check_for_space(char *s)
{
	int	i;
	int	space;

	if (!s)
		return (0);
	i = 0;
	space = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]))
			space++;
		i++;
	}
	if (space == i)
		return (2);
	else if (space > 0)
		return (1);
	else
		return (0);
}
