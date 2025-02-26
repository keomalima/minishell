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

static t_list	*ft_split_into_list_space(char *s, t_expand *expand)
{
	t_list	*list;
	char	*str;
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
			str = ft_calloc((ft_strlen_between_space(&s[i]) + 1), sizeof(char));
			if (!str)
				ft_clear_expand(expand, 12);
			ft_strlcpy(str, &s[i], (ft_strlen_between_space(&s[i]) + 1));
			ft_lstadd_back(&list, ft_lstnew(str));
			i += ft_strlen_between_space(&s[i]);
		}
	}
	return (list);
}

static size_t	ft_strlen_joined_space(t_list *list, int *check_empty)
{
	size_t		len;
	t_list		*current;

	current = list;
	len = 0;
	while (current)
	{
		if (current->content)
			*check_empty += 1;
		len += ft_strlen(current->content);
		current = current->next;
	}
	return (len);
}

char	*ft_joined_space_list(t_list *list, t_expand *expand)
{
	size_t		len;
	t_list		*current;
	char		*dest;
	int			check_empty;

	check_empty = 0;
	len = ft_strlen_joined_space(list, &check_empty);
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1 + (ft_lstsize(list) - 1)), sizeof(char));
	if (!dest)
	{
		ft_lstclear(&list, &del_content);
		ft_clear_expand(expand, 12);
	}
	current = list;
	while (current)
	{
		ft_strlcpy(&dest[ft_strlen(dest)], current->content,
			(ft_strlen(current->content) + 1));
		if (current->next)
			dest[ft_strlen(dest)] = ' ';
		current = current->next;
	}
	return (dest);
}

char	*clear_string_space(char *s, t_expand *expand)
{
	t_list	*list;
	char	*dest;

	list = ft_split_into_list_space(s, expand);
	if (!list)
		ft_clear_expand(expand, 1);
	dest = ft_joined_space_list(list, expand);
	ft_lstclear(&list, &del_content);
	return (dest);
}
