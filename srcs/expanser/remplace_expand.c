#include "minishell.h"

t_list	*ft_remplace_by_expand(char *str, t_expand *expand, char quote)
{
	char	*s;
	t_list	*new;

	if (!str || str[0] != '$')
		return (ft_lstnew(str));
	s = str + 1;
	if (!s)
		return (ft_lstnew(NULL));
	if (*s == '?')
		new = ft_lstnew(exp_exit_code(expand));
	else if (ft_strcmp(s, "UID") == 0)
		new = ft_lstnew(exp_uid(expand));
	else if (ft_isdigit(*s))
		new = ft_lstnew(exp_digit_variable(s, expand));
	else if (ft_isquote(*s) && quote != '\"')
		new = ft_lstnew(exp_quote_variable(s, expand));
	else if (ft_isalpha(*s))
		new = ft_lstnew(exp_valid_variable(s, expand));
	else
		new = ft_lstnew(ft_strdup(str));
	ft_free(&str);
	return (new);
}
