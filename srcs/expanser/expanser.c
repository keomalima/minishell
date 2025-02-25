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

char	*ft_split_expand(char *s, int *j, t_expand *expand, t_list **dest)
{
	char	*str;
	size_t	len;

	len = ft_strlen_expand(&s[*j]);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
	{
		ft_lstclear(dest, &del_content);
		ft_clear_expand(expand, 12);
	}
	ft_strlcpy(str, &s[*j], (len + 1));
	*j = *j + len - 1;
	return (str);
}


t_list	*ft_remplace_by_expand(t_list *node, t_ms *ms, char quote)
{
	char	*s;
	t_list	*new;

	// printf("Remplace expand [%s]\n", (char *)node->content);
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


char	*ft_clean_quote_string(char *s, t_expand *expand)
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

t_list	*ft_reset_quote(t_list **dest, t_list **initial_list, t_ms *ms)
{
	char	*joined;
	char	*str;
	t_list	*new;

	joined = ft_joined_list(*dest, initial_list, ms);
	str = ft_calloc((ft_strlen(joined) + 3), sizeof(char));
	if (!str)
	{
		ft_lstclear(dest, &del_content);
		ft_lstclear(initial_list, &del_content);
		exit_handler(ms, 12);
	}
	str[0] = '\"';
	ft_strlcpy(&str[1], joined, (ft_strlen(joined) + 1));
	str[ft_strlen(str)] = '\"';
	new = ft_lstnew(str);
	if (!str)
	{
		ft_lstclear(dest, &del_content);
		ft_lstclear(initial_list, &del_content);
		exit_handler(ms, 12);
	}
	ft_free(&joined);
	ft_lstclear(dest, &del_content);
	return (new);
}

t_list	*ft_expanded_node(char *s, t_expand *expand, char quote)
{
	t_list	*dest;
	t_list	*new;
	int		i;
	char	*tmp;
	char	*split;

	if (s && *s && *s == '\"')
		tmp = ft_clean_quote_string(s, expand);
	else
		tmp = ft_strdup(s);
	dest = NULL;
	i = 0;
	while (tmp[i])
	{
		split = ft_split_expand(tmp, &i, expand, &dest);
		new = ft_lstnew(split);
		if (!new)
		{
			ft_lstclear(&dest, &del_content);
			ft_clear_expand(expand, 12);
		}
		if (new->content && ((char *)new->content)[0] == '$')
			new = ft_remplace_by_expand(new, expand->ms, quote);
		if (!new)
		{
			ft_lstclear(&dest, &del_content);
			ft_clear_expand(expand, 12);
		}
		if (new->content)
			ft_lstadd_back(&dest, new);
		i++;
	}
	ft_free(&tmp);
	if (s && *s && *s == '\"')
		dest = ft_reset_quote(&dest, &expand->initial_list, expand->ms);
	return(dest);
}


t_list	*ft_expanded_list(t_expand *expand)
{
	t_list	*current;
	t_list	*expanded_list;
	t_list	*new;

	current = expand->initial_list;
	expanded_list = NULL;
	while (current)
	{
		if (!current->content || !*(char *)current->content)
			continue;
		if (*(char *)current->content == '\'' || ft_count_exp(current->content) == 0)
			new = ft_lstnew(ft_strdup(current->content));
		else
			new = ft_expanded_node(current->content, expand, ((char *)current->content)[0]);
		if (!new)
		{
			ft_lstclear(&expand->initial_list, &del_content);
			ft_lstclear(&expanded_list, &del_content);
			exit_handler(expand->ms, 12);
		}
		ft_lstadd_back(&expanded_list, new);
		current = current->next;
	}
	return (expanded_list);
}
