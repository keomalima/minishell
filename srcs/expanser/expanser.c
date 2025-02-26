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
			ft_lstclear(list, &del_content);
			ft_clear_expand(expand, 12);
		}
		str[0] = '\"';
		ft_strlcpy(&str[1], joined, (ft_strlen(joined) + 1));
		str[ft_strlen(str)] = '\"';
		ft_lstclear(list, &del_content);
		*list = ft_lstnew(str);
		ft_free(&joined);
	}
}

void	ft_handle_quote(char *s, char **tmp, t_expand *expand, int step)
{
	if (step == 1)
	{
		if (s && *s && *s == '\"')
			*tmp = ft_clean_quote_string(s, expand);
		else
			*tmp = ft_strdup(s);
	}
}

static t_list	*ft_expanded_node(char *s, t_expand *expand, char quote)
{
	t_list	*new_list;
	t_list	*node;
	int		i;
	char	*tmp;

	new_list = NULL;
	ft_handle_quote(s, &tmp, expand, 1);
	i = 0;
	while (tmp[i])
	{
		node = ft_remplace_by_expand(ft_split_expand(tmp, &i, expand),
				expand, quote);
		if (!node)
			ft_clear_expand(expand, 12);
		if (node->content)
			ft_lstadd_back(&new_list, node);
		else
			ft_lstclear(&node, &del_content);
		i++;
	}
	ft_free(&tmp);
	ft_reset_quote(s, &new_list, expand);
	if (!new_list)
		new_list = ft_lstnew(NULL);
	return (new_list);
}

void	ft_set_expanded_list(t_expand *expand)
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
		if (*s == '\'' || ft_count_exp(s) == 0)
			new_node = ft_lstnew(ft_strdup(s));
		else
			new_node = ft_expanded_node(s, expand, s[0]);
		if (!new_node)
			ft_clear_expand(expand, 12);
		ft_lstadd_back(&expand->exp_list, new_node);
		current = current->next;
	}
}
