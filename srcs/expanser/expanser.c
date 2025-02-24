#include "minishell.h"

size_t	ft_strlen_expand(char *s)
{
	int	i;

	if (!s)
		return (0);
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

char	*ft_split_expand(char *s, int *j)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_expand(&s[*j]);
	// printf("len = %zu\n", len);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[*j], (len + 1));
	*j = *j + len - 1;
	return (dest);
}


t_list	*ft_remplace_by_expand(t_list *node, t_ms *ms, char quote)
{
	char	*s;
	t_list	*new;

	s = node->content + 1;
	if (!s)
		return (node);
	if (*s == '?')
		new = ft_lstnew(exp_exit_code(s, ms));
	else if (ft_strcmp(s, "UID") == 0)
		new = ft_lstnew(exp_uid(s));
	else if (ft_isdigit(*s))
		new = ft_lstnew(exp_digit_variable(s));
	else if (ft_isquote(*s) && quote != '\"')
		new = ft_lstnew(exp_quote_variable(s));
	else if (ft_isalpha(*s))			///////
		new = ft_lstnew(exp_valid_variable(s, ms));
	else
		new = ft_lstnew(ft_strdup(node->content));
	ft_lstclear(&node, &del_content);
	return (new);
}

t_list	*expand2(char *s, t_ms *ms, char quote)
{
	t_list	*res;
	t_list	*new;
	int		i;
	int		exp;

	res = NULL;
	i = 0;
	while (s[i])
	{
		exp = 0;
		new = ft_lstnew(ft_split_expand(s, &i));
		// printf(blue"before expanser -> %s\n"RESET, (char *)new->content);
		if (new->content && ((char *)new->content)[0] == '$')
		{
			new = ft_remplace_by_expand(new, ms, quote);
			exp = 1;
		}
		// printf(blue"	after expanser -> %s\n"RESET, (char *)new->content);
		if (((char *)new->content)[0] == 0 && exp == 1)
			ft_lstclear(&new, &del_content);
		else
			ft_lstadd_back(&res, new);
		i++;
	}
	// t_list *current = res;
	// while (current)
	// {
	// 	printf(blue"list -> %s\n"RESET, (char *)current->content);
	// 	current = current->next;
	// }
	return (res);
}

t_list	*ft_expanded_node(t_list *node, t_ms *ms, t_list **list, char quote)
{
	t_list	*expanded_node;

	if (ft_count_exp(node->content) == 0)
		return (ft_lstnew(ft_strdup(node->content)));
	if (!node->content)
	{
		ft_lstclear(list, &del_content);
		exit_handler(ms, 12);
	}

	expanded_node = expand2(node->content, ms, quote);
	// expanded_node = ft_lstnew(ft_strdup(node->content));
	return(expanded_node);
}

t_list	*ft_clean_quote_node(char *s)
{
	t_list	*clean_node;
	size_t	len;
	char	*content;

	len = ft_strlen(s) - 2;
	content = ft_calloc((len + 1), sizeof(char));
	if (!content)
		return (NULL);
	ft_strlcpy(content, &s[1], ft_strlen(&s[1]));
	clean_node = ft_lstnew(content);
	if (!clean_node)
		return (NULL);
	return (clean_node);
}


t_list	*ft_expanded_list(t_list *list, t_ms *ms)
{
	t_list	*current;
	t_list	*expanded_list;
	t_list	*clean_node;
	char	*s;

	current = list;
	expanded_list = NULL;
	while (current)
	{
		s = current->content;
		clean_node = ft_clean_quote_node(current->content);
		if (s && *s && ft_isquote(s[0]))
		{
			if (s[0] == '\"')
				ft_lstadd_back(&expanded_list, ft_expanded_node(clean_node, ms, &current, s[0]));
			else
				ft_lstadd_back(&expanded_list, clean_node);
		}
		else
			ft_lstadd_back(&expanded_list, ft_expanded_node(current, ms, &current, 0));

		ft_lstclear(&clean_node, &del_content);
		current = current->next;
	}
	(void)ms;
	ft_lstclear(&list, &del_content);
	return (expanded_list);
}