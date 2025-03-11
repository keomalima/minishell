#include "minishell.h"

static size_t	ft_strlen_between_space(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

static t_list	*ft_node_space_creator(t_expand *expand, char *s, t_list **list)
{
	char	*str;
	t_list	*node;

	str = ft_calloc((ft_strlen_between_space(s) + 1), sizeof(char));
	if (!str)
		ft_clear_expand(expand, 12);
	ft_strlcpy(str, s, (ft_strlen_between_space(s) + 1));
	node = ft_lstnew(str);
	if (!node)
	{
		free(str);
		ft_lstclear(list);
	}
	return (node);
}

static t_list	*ft_split_into_list_space(char *s, t_expand *expand)
{
	t_list	*list;
	t_list	*node;
	int		i;

	if (!s)
		return (ft_lstnew(NULL));
	list = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			node = ft_node_space_creator(expand, &s[i], &list);
			ft_lstadd_back(&list, node);
			i += ft_strlen_between_space(&s[i]);
		}
	}
	return (list);
}

char	*clear_string_space(char *s, t_expand *expand)
{
	t_list	*list;
	char	*dest;
	int		space_status;

	space_status = ft_check_for_space(s);
	if (space_status == 2)
		return (NULL);
	list = ft_split_into_list_space(s, expand);
	if (!list)
		ft_clear_expand(expand, 1);
	dest = ft_joined_space_list(list, expand);
	ft_lstclear(&list);
	return (dest);
}