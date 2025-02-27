#include "minishell.h"

void	ft_complete_cmd(t_cmd *new, t_token *token, t_index *index, t_ms *ms)
{
	token->content = ft_translate(token->content, ms);
	if (!new->cmd || !new->files)
		exit_handler(ms, 12);
	if (token->type == OPP && !ft_strcmp(token->content, ">"))
		new->redir = OUT_TRUNC;
	else if (token->type == OPP && !ft_strcmp(token->content, ">>"))
		new->redir = OUT_APPEND;
	else if (token->prev && token->prev->type == OPP
			&& !is_opp_file(token->prev->content))
		new->files[index->file_i++] = ft_new_file(token, ms);
	else if (token->type != OPP)
	{
		if (token->content)
			new->cmd[index->cmd_i++] = token->content;
	}
}

void	ft_parsing_allocation(t_cmd *new, t_ms *ms)
{
	new->cmd = ft_calloc((new->cmd_size + 1), sizeof(char *));
	new->files = ft_calloc((new->files_size + 1), sizeof(t_files *));
	if (!new->cmd || !new->files)
		exit_handler(ms, 12);
}

void	parse_cmd(t_ms *ms)
{
	t_cmd	*new;
	t_token	*token;
	t_index	index;

	token = ms->token;
	new = NULL;
	while (token)
	{
		new = ft_lst_new_cmd(ms);
		ft_find_cmd_size(token, new);
		ft_parsing_allocation(new, ms);
		ft_initialize_index(&index);
		while (token && ft_strcmp(token->content, "|"))
		{
			ft_complete_cmd(new, token, &index, ms);
			token = token->next;
		}
		if (token && !ft_strcmp(token->content, "|"))
		{
			new->redir = PIPE;
			token = token->next;
			ft_lstadd_back_cmd(&ms->cmd, new);
		}
	}
	ft_lstadd_back_cmd(&ms->cmd, new);
}
