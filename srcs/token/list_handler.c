#include "minishell.h"

t_token	*ft_lstnew_ms(t_ms *ms, char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		exit_handler(ms, 1);
	new->content = content;
	new->type = ms->lexer.state;
	new->prev = NULL;
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
		new->prev = last;
		last->next = new;
	}
}
