#include "minishell.h"

void	del_content(void *content)
{
	if(content)
		free(content);
}

char	*ft_joined_list(t_list *list, t_ms *ms)
{
	size_t		len;
	t_list	*current;
	char		*dest;
	int			check_empty;

	current = list;
	check_empty = 0;
	len = 0;
	while (current)
	{
		if (current->content)
			check_empty++;
		len += ft_strlen(current->content);
		current = current->next;
	}
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		ft_lstclear(&list, &del_content);
		exit_handler(ms, 12);
	}
	current = list;
	while (current)
	{
		ft_strlcpy(&dest[ft_strlen(dest)], current->content, (ft_strlen(current->content) + 1));
		// printf("joined dest {%s}\n", dest);
		current = current->next;
	}
	return (dest);
}
char	*ft_joined_space_list(t_list *list, t_ms *ms)
{
	size_t		len;
	t_list	*current;
	char		*dest;
	int			check_empty;

	current = list;
	len = 0;
	check_empty = 0;
	while (current)
	{
		if (current->content)
			check_empty++;
		len += ft_strlen(current->content);
		current = current->next;
	}
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1 + (ft_lstsize(list) - 1)), sizeof(char));
	if (!dest)
	{
		ft_lstclear(&list, &del_content);
		exit_handler(ms, 12);
	}
	current = list;
	while (current)
	{
		ft_strlcpy(&dest[ft_strlen(dest)], current->content, (ft_strlen(current->content) + 1));
		if (current->next)
			dest[ft_strlen(dest)] = ' ';
		// printf("joined dest {%s}\n", dest);
		current = current->next;
	}
	return (dest);
}
