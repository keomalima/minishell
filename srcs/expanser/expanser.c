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

static void	ft_reset_quote(char *s, t_list **list, t_expand *expand)
{
	char	*joined;
	char	*str;

	if (s && *s && *s == '\"')
	{
		joined = ft_joined_list(*list, expand);
		str = ft_calloc((ft_strlen(joined) + 3), sizeof(char));
		if (!str)
		{
			ft_free(&joined);
			ft_lstclear(list);
			ft_clear_expand(expand, 12);
		}
		str[0] = '\"';
		ft_strlcpy(&str[1], joined, (ft_strlen(joined) + 1));
		str[ft_strlen(str)] = '\"';
		ft_lstclear(list);
		*list = ft_lstnew(str);
		ft_free(&joined);
	}
}

static char	*ft_handle_quote(char *s, t_expand *expand)
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

static t_list	*ft_expanded_node(char *s, t_expand *expand, char quote)
{
	t_list		*node;
	int			i;
	t_exp_utils	util;

	util.new_list = NULL;
	util.clean_quote = ft_handle_quote(s, expand);
	i = 0;
	while (util.clean_quote[i])
	{
		node = ft_remplace_by_expand(ft_split_expand(util.clean_quote, &i, expand), expand, quote, &util);
		if (!node)
			ft_clear_expand(expand, 12);
		if (node->content)
			ft_lstadd_back(&util.new_list, node);
		else
			ft_lstclear(&node);
		i++;
	}
	ft_free(&util.clean_quote);
	ft_reset_quote(s, &util.new_list, expand);
	if (!util.new_list)
		util.new_list = ft_lstnew(NULL);
	return (util.new_list);
}

void	ft_set_expanded_list(t_expand *expand, int hd)
{
	t_list	*current;
	t_list	*new_node;
	char	*s;

	current = expand->initial_list;
	while (current)
	{
		s = current->content;
		if (!s || !*s)
		{
			current = current->next;
			continue ;
		}
		if (hd == 0 && (*s == '\'' || ft_count_exp(s) == 0))
			new_node = ft_lstnew(ft_strdup(s));
		else
			new_node = ft_expanded_node(s, expand, s[0]);
		if (!new_node)
			ft_clear_expand(expand, 12);
		ft_lstadd_back(&expand->exp_list, new_node);
		current = current->next;
	}
}
