#include "minishell.h"

void	del_content(void *content)
{
	if(content)
		free(content);
}
char	*ft_joined_list(t_list *list, t_ms *ms)
{
	size_t	len;
	t_list	*current;
	char	*dest;

	current = list;
	len = 0;
	while (current)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
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