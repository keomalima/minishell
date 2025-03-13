#include "minishell.h"

static t_list	*exp_other_case(char *str, t_expand *expand, t_ex_u *util)
{
	char	*tmp;
	t_list	*new;

	tmp = ft_strdup(str);
	if (!tmp)
		ft_expand_alloc_failure(expand, util, str);
	new = ft_lstnew(tmp);
	return (new);
}

t_list	*ft_remp_expand(char *str, t_expand *expand, char quote, t_ex_u *util)
{
	char	*s;
	t_list	*new;

	if (!str || str[0] != '$')
		return (ft_lstnew(str));
	s = str + 1;
	if (!s)
		return (ft_lstnew(NULL));
	if (*s == '?')
		new = ft_lstnew(exp_exit_code(str, expand, util));
	else if (ft_strcmp(s, "UID") == 0)
		new = ft_lstnew(exp_uid(str, expand, util));
	else if (ft_isdigit(*s))
		new = ft_lstnew(exp_digit_variable(str, expand, util));
	else if (ft_isquote(*s) && quote != '\"')
		new = ft_lstnew(exp_quote_variable(str, expand, util));
	else if (ft_isalpha(*s))
		new = ft_lstnew(exp_valid_variable(str, expand, util));
	else
		new = exp_other_case(str, expand, util);
	if (!new)
		ft_expand_alloc_failure(expand, util, str);
	ft_free(&str);
	return (new);
}
