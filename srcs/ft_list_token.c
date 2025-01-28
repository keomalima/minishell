#include "../includes/minishell.h"

t_token *create_new_token(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_token(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!token_list || !new)
		return ;
	if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	last = ft_lstlast_token(*token_list);
	new->prev = last;
	last->next = new;
}

void	del_content(void *content)
{
	if(content)
		free(content);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*temp;
	t_token	*next;

	if (!lst || !*lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		del(temp->content);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*lst = NULL;
}