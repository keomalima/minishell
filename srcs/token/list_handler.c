#include "minishell.h"

t_token	*ft_lstnew_tk(t_ms *ms, char *content)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(content);
		exit_handler(ms, 1);
	}
	new->type = ms->lexer.state;
	new->content = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_tk(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_tk(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_tk(*lst);
		new->prev = last;
		last->next = new;
	}
}
