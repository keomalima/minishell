#include "../includes/minishell.h"

t_token *create_new_token(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->word = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_lstlast_ms(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_ms(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!token_list || !new)
		return ;
	if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	last = ft_lstlast_ms(*token_list);
	last->next = new;
	new->prev = last;
}
