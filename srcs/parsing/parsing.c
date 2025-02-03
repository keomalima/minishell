#include "minishell.h"

void ft_complete_cmd(t_cmd *new, t_token *token, t_index *index)
{
	//	set redirection
	if (ft_strcmp(token->content, ">") == 0)
		new->redir = OUT_TRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		new->redir = OUT_APPEND;
	//	set infile / outfile
	else if (token->prev && (ft_strcmp(token->prev->content, ">") == 0 || ft_strcmp(token->prev->content, ">>") == 0))
		new->outfile[index->out_i++] = token->content;
	else if (token->prev && ft_strcmp(token->prev->content, "<") == 0)
		new->infile[index->in_i++] = token->content;
	//	set command
	else if (token->type != OPP)
	{
		if (ft_strchr(token->content, '$') && token->type != SQ)
			token->content = expanser(token->content);
		new->cmd[index->cmd_i++] = token->content;
	}
}

void	ft_find_cmd_size(t_token *token, t_cmd *new)
{
	int	redir;

	redir = 0;
	while (token && ft_strcmp(token->content, "|") != 0)
	{
		if (ft_strcmp(token->content, "<") == 0 || ft_strcmp(token->content, ">") == 0 || ft_strcmp(token->content, ">>") == 0)
		{
			if (ft_strcmp(token->content, "<") == 0)
				new->infile_size++;
			else if (ft_strcmp(token->content, ">") == 0 || ft_strcmp(token->content, ">>") == 0)
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

void parse_cmd(t_ms *ms)
{
	t_cmd	*new;
	t_token	*token;
	t_index	index;

	token = ms->token;
	new = NULL;
	while (token)
	{
		new = ft_lst_new_cmd();
		ft_find_cmd_size(token, new);
		///////////////////// what if size < 0 ??
		new->cmd = ft_calloc((new->cmd_size + 1), sizeof(char *));
		new->infile = ft_calloc((new->infile_size + 1), sizeof(char *));
		new->outfile = ft_calloc((new->outfile_size + 1), sizeof(char *));
		//////////////////
		ft_initialize_index(&index);
		while (token && ft_strcmp(token->content, "|") != 0)
		{
			ft_complete_cmd(new, token, &index);
			token = token->next;
		}
		if (token && ft_strcmp(token->content, "|") == 0)
		{
			if (!new->outfile)
				new->redir = PIPE;
			token = token->next;
			ft_lstadd_back_cmd(&ms->cmd, new);
		}
	}
	ft_lstadd_back_cmd(&ms->cmd, new);
}
