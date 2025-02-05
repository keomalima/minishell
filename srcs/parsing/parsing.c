#include "minishell.h"

void	ft_complete_cmd(t_cmd *new, t_token *token, t_index *index, t_ms *ms)
{
	if (token->type == OPP && ft_strcmp(token->content, ">") == 0)
		new->redir = OUT_TRUNC;
	else if (token->type == OPP && ft_strcmp(token->content, ">>") == 0)
		new->redir = OUT_APPEND;
	else if (token->prev && token->prev->type == OPP && (ft_strcmp(token->prev->content, ">") == 0 || ft_strcmp(token->prev->content, ">>") == 0))
		new->outfile[index->out_i++] = ft_new_outfile(token, ms);
	else if (token->prev && token->prev->type == OPP && (ft_strcmp(token->prev->content, "<") == 0 || ft_strcmp(token->prev->content, "<<") == 0))
		new->infile[index->in_i++] = ft_new_infile(token, ms);
	else if (token->type != OPP)
	{
		if (ft_strchr(token->content, '$') && token->type != SQ)
			token->content = expanser(token->content, ms);
		new->cmd[index->cmd_i++] = token->content;
	}
}

void	ft_find_cmd_size(t_token *token, t_cmd *new)
{
	int	redir;

	redir = 0;
	while (token && ft_strcmp(token->content, "|") != 0)
	{
		if (token->type == OPP && (ft_strcmp(token->content, "<") == 0
			|| ft_strcmp(token->content, "<<") == 0
			|| ft_strcmp(token->content, ">") == 0
			|| ft_strcmp(token->content, ">>") == 0))
		{
			if (ft_strcmp(token->content, "<") == 0 || ft_strcmp(token->content, "<<") == 0)
				new->infile_size++;
			else
				new->outfile_size++;
			redir += 2;
		}
		new->cmd_size++;
		token = token->next;
	}
	if ((new->cmd_size - redir) > 0)
		new->cmd_size = new->cmd_size - redir;
}

void	ft_initialize_index(t_index *index)
{
	index->cmd_i = 0;
	index->in_i = 0;
	index->out_i = 0;
}

void	ft_parsing_allocation(t_cmd *new, t_ms *ms)
{
	new->cmd = ft_calloc((new->cmd_size + 1), sizeof(char *));
	new->infile = ft_calloc((new->infile_size + 1), sizeof(t_infile *));
	new->outfile = ft_calloc((new->outfile_size + 1), sizeof(t_outfile *));
	if (!new->cmd || !new->infile || !new->outfile)
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
		while (token && ft_strcmp(token->content, "|") != 0)
		{
			ft_complete_cmd(new, token, &index, ms);
			token = token->next;
		}
		if (token && ft_strcmp(token->content, "|") == 0)
		{
			new->redir = PIPE;
			token = token->next;
			ft_lstadd_back_cmd(&ms->cmd, new);
		}
	}
	ft_lstadd_back_cmd(&ms->cmd, new);
}
