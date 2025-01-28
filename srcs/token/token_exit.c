#include "minishell.h"

void	ft_lstdelone_ms(t_token *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

void	ft_lstclear_ms(t_token **lst)
{
	t_token	*temp;

	if (lst)
	{
		while (*lst)
		{
			temp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone_ms(temp);
		}
	}
}

void	exit_handler(t_ms *ms, int exit_code)
{
	ft_lstclear_ms(&ms->token);
	exit(exit_code);
}
