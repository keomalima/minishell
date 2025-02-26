#include "minishell.h"

size_t	ft_strlen_joined_list(t_list *list, int *check_empty)
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

char	*ft_joined_list(t_list *list, t_expand *expand)
{
	size_t		len;
	t_list		*current;
	char		*dest;
	int			check_empty;

	check_empty = 0;
	len = ft_strlen_joined_list(list, &check_empty);
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	current = list;
	while (current)
	{
		ft_strlcpy(&dest[ft_strlen(dest)], current->content,
			(ft_strlen(current->content) + 1));
		current = current->next;
	}
	return (dest);
}
