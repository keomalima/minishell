#include "minishell.h"

void ft_complete_cmd(t_cmd *new, t_ms *ms, int *i)
{
	//	set redirection
	if (ft_strcmp(ms->token->content, ">") == 0)
		new->redir = OUT_TRUNC;
	else if (ft_strcmp(ms->token->content, ">>") == 0)
		new->redir = OUT_APPEND;
	//	set infile / outfile
	else if (ms->token->prev && (ft_strcmp(ms->token->prev->content, ">") == 0 || ft_strcmp(ms->token->prev->content, ">>") == 0))
		new->outfile = ms->token->content;
	else if (ms->token->prev && ft_strcmp(ms->token->prev->content, "<") == 0)
		new->infile = ms->token->content;
	//	set command
	else if (*ms->token->content && ms->token->type != OPP)
	{
		new->cmd[*i] = ms->token->content;
		(*i)++;
	}
}

char	*ft_strchr_parse(char *set, char *str)
{
	int	i;

	while (*str)
	{
		i = 0;
		while (set[i])
		{
			if (*str == set[i++])
				return (str);
		}
		str++;
	}
	return (NULL);
}

int	ft_find_cmd_size(t_token *token)
{
	int	cmd_size;
	int	redir;

	cmd_size = 0;
	redir = 0;

	while (token && ft_strcmp(token->content, "|"))
	{
		if (ft_strchr_parse(token->content, "<>"))
			redir += 2;
		cmd_size++;
		token = token->next;
	}
	if ((cmd_size - redir) > 0)
		return (cmd_size - redir);
	else
		return (cmd_size);
}

void	parse_cmd(t_ms *ms)
{
	t_cmd	*new;
	int		i;

	new = NULL;
	while (ms->token)
	{
		new = ft_lst_new_cmd();
		new->cmd_size = ft_find_cmd_size(ms->token);
		///////////////////// what if size < 0 ??
		new->cmd = ft_calloc((new->cmd_size + 1), sizeof(char *));
		//////////////////
		i = 0;
		while (ms->token && ft_strcmp(ms->token->content, "|") != 0)
		{
			ft_complete_cmd(new, ms, &i);
			ms->token = ms->token->next;
		}
		if (ms->token && ft_strcmp(ms->token->content, "|") == 0)
		{
			if (!new->outfile)
				new->redir = PIPE;
			ms->token = ms->token->next;
			ft_lstadd_back_cmd(&ms->cmd, new);
		}
	}
	ft_lstadd_back_cmd(&ms->cmd, new);
}
