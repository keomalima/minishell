#include "minishell.h"

t_files	*ft_new_file(t_token *token, t_ms *ms)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (!new)
		exit_handler(ms, 12);
	new->name = token->content;
	new->is_lim = 0;
	if (!ft_strcmp(token->prev->content, "<<"))
		new->is_lim = 1;
	new->type = IN;
	if (token->prev && !ft_strcmp(token->prev->content, ">>"))
		new->type = OUT_APPEND;
	else if (token->prev && !ft_strcmp(token->prev->content, ">"))
		new->type = OUT_TRUNC;
	return (new);
}

t_cmd	*ft_lst_new_cmd(t_ms *ms)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_handler(ms, 12);
	new->cmd = NULL;
	new->cmd_size = 0;
	new->files = NULL;
	new->files_size = 0;
	new->redir = UNDEFINED;
	new->next = NULL;
	new->nb_expand = 0;
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
