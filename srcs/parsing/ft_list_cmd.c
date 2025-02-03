#include "minishell.h"

t_cmd	*ft_lst_new_cmd(t_ms *ms)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_handler(ms, 12);
	new->cmd = NULL;
	new->cmd_size = 0;
	new->infile = NULL;
	new->infile_size = 0;
	new->outfile = NULL;
	new->outfile_size = 0;
	new->redir = UNDEFINED;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new)
{
	t_cmd	*last;

	if (!cmd_list || !new)
		return ;
	if (!*cmd_list)
	{
		*cmd_list = new;
		return ;
	}
	last = ft_lstlast_cmd(*cmd_list);
	last->next = new;
}
