#include "../includes/minishell.h"

void ft_complete_cmd(t_cmd *new, t_token *token_list)
{
	if (token_list->type == IN_OPERATOR)
	{
		if (ft_strcmp(token_list->content, '>') == 0)
			new->redir_type = OUT_TRUNC;
		if (ft_strcmp(token_list->content, '>>') == 0)
			new->redir_type = OUT_APPEND;
	}
}

void parse_cmd(t_cmd **cmd_list, t_token *token_list)
{
	t_cmd	*new;
	while (token_list)
	{
		new = ft_lst_new_cmd();
		while (token_list && ft_strcmp(token_list->type, '|') != 0)
		{
			ft_complete_cmd(new, token_list);
			token_list = token_list->next;
		}
		if (token_list && ft_strcmp(token_list->type, '|') == 0 && new->outfile == NULL)
			new->redir_type = PIPE;
		ft_lstadd_back_cmd(cmd_list, new);
	}
}