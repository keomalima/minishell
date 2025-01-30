#include "minishell.h"

void ft_complete_cmd(t_cmd *new, t_token *token, int *i)
{
	//	set redirection
	if (ft_strcmp(token->content, ">") == 0)
		new->redir = OUT_TRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		new->redir = OUT_APPEND;
	//	set infile / outfile
	else if (token->prev && (ft_strcmp(token->prev->content, ">") == 0 || ft_strcmp(token->prev->content, ">>") == 0))
		new->outfile = token->content;
	else if (token->prev && ft_strcmp(token->prev->content, "<") == 0)
		new->infile = token->content;
	//	set command
	else if (*token->content && token->type != OPP)
	{
		new->cmd[*i] = token->content;
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
	t_token	*token;
	int		i;

	new = NULL;
	token = ms->token;
	while (token)
	{
		new = ft_lst_new_cmd(ms);
		new->cmd_size = ft_find_cmd_size(token);
		///////////////////// what if size < 0 ??
		new->cmd = ft_calloc((new->cmd_size + 1), sizeof(char *));
		if (!new->cmd)
		{
			free(new);
			exit_handler(ms, 12);
		}
		i = 0;
		while (token && ft_strcmp(token->content, "|") != 0)
		{
			ft_complete_cmd(new, token, &i);
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
