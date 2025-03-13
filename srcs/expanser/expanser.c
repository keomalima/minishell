#include "minishell.h"

void	ft_expand_alloc_failure(t_expand *expand, t_ex_u *util, char *str)
{
	free(util->clean_quote);
	ft_lstclear(&util->new_list);
	free(str);
	ft_clear_expand(expand, 12);
}

static void	ft_reset_quote(char *s, t_ex_u *util, t_expand *expand)
{
	char	*joined;
	char	*str;

	if (s && *s && *s == '\"')
	{
		joined = ft_joined_list(util, expand);
		str = ft_calloc((ft_strlen(joined) + 3), sizeof(char));
		if (!str)
		{
			ft_free(&joined);
			ft_lstclear(&util->new_list);
			ft_clear_expand(expand, 12);
		}
		str[0] = '\"';
		ft_strlcpy(&str[1], joined, (ft_strlen(joined) + 1));
		str[ft_strlen(str)] = '\"';
		ft_lstclear(&util->new_list);
		util->new_list = ft_lstnew(str);
		if (!util->new_list)
		{
			ft_free(&joined);
			ft_expand_alloc_failure(expand, util, str);
		}
		ft_free(&joined);
	}
}

static t_list	*ft_expanded_node(char *s, t_expand *expand, char quote)
{
	t_list		*node;
	int			i;
	t_ex_u		util;

	util.new_list = NULL;
	util.clean_quote = ft_handle_quote(s, expand);
	i = 0;
	while (util.clean_quote[i])
	{
		node = ft_remp_expand
			(ft_split_expand(util.clean_quote, &i, expand),
				expand, quote, &util);
		if (!node)
			ft_clear_expand(expand, 12);
		if (node->content)
			ft_lstadd_back(&util.new_list, node);
		else
			ft_lstclear(&node);
		i++;
	}
	ft_free(&util.clean_quote);
	ft_reset_quote(s, &util, expand);
	if (!util.new_list)
		util.new_list = ft_lstnew(NULL);
	return (util.new_list);
}

static t_list	*safe_lstnew_strdup(char *s, t_expand *expand)
{
	char	*tmp;
	t_list	*new_node;

	tmp = ft_strdup(s);
	if (!tmp)
		ft_clear_expand(expand, 12);
	new_node = ft_lstnew(tmp);
	return (new_node);
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
			new_node = safe_lstnew_strdup(s, expand);
		else
			new_node = ft_expanded_node(s, expand, s[0]);
		if (!new_node)
			ft_clear_expand(expand, 12);
		ft_lstadd_back(&expand->exp_list, new_node);
		current = current->next;
	}
}
