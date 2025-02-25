#include "minishell.h"

void	del_content(void *content)
{
	if(content)
		free(content);
}

char	*ft_joined_list(t_list *list, t_list **initial_list, t_ms *ms)
{
	size_t		len;
	t_list		*current;
	char		*dest;

	current = list;
	len = 0;
	while (current)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	if (len == 0)
		return (NULL);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
	{
		ft_lstclear(initial_list, &del_content);
		ft_lstclear(&list, &del_content);
		exit_handler(ms, 12);
	}
	current = list;
	while (current)
	{
		ft_strlcpy(&dest[ft_strlen(dest)], current->content, (ft_strlen(current->content) + 1));
		current = current->next;
	}
	return (dest);
}

char	*ft_joined_list_without_quote(t_list *list, t_ms *ms)
{
	t_list	*current;
	size_t	len;
	char	*dest;
	char	*tmp;
	int		check_empty;

	current = list;
	len = 0;
	check_empty = 0;
	while (current)
	{
		if (current->content)
			check_empty++;
		if (current->content && ft_isquote(((char *)current->content)[0]))
			len += (ft_strlen(current->content) - 2);
		else
		{
			tmp = clear_string_space(current->content);
			len += ft_strlen(tmp);
			if (len > 0 && current->content && ((char *)current->content)[0] && ft_isspace(((char *)current->content)[0]))
				len++;
			ft_free(&tmp);
		}
		current = current->next;
	}
	// printf("len = %zu\n", len);
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1), sizeof(char));	//////////////////////////////
	if (!dest)
	{
		ft_lstclear(&list, &del_content);
		exit_handler(ms, 12);
	}
	current = list;
	while (current)
	{
		if (current->content && ft_isquote(((char *)current->content)[0]))
			ft_strlcpy(&dest[ft_strlen(dest)], &((char *)current->content)[1], ft_strlen(current->content) - 1);
		else
		{
			tmp = clear_string_space(current->content);
			if (dest && *dest && current->content && ((char *)current->content)[0] && ft_isspace(((char *)current->content)[0]))
			{
				dest[ft_strlen(dest)] = ' ';
			}
			ft_strlcpy(&dest[ft_strlen(dest)], tmp, (ft_strlen(tmp) + 1));
			ft_free(&tmp);
		}
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
