#include "../includes/minishell.h"

t_token	*ft_lstnew_ms(char *content, e_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_ms(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_ms(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_ms(*lst);
		last->next = new;
	}
}