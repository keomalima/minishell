#include "minishell.h"

static size_t	is_redir(const char *content)
{
	int			i;
	const char	*valid_ops[] = {">", ">>", "<", "<>", "<<", "<<<", NULL};

	i = 0;
	while (valid_ops[i])
	{
		if (!ft_strcmp(content, valid_ops[i]))
			return (0);
		i++;
	}
	return (1);
}

int	lexical_error(t_ms *ms, char *str_err)
{
	t_token	*token;

	token = ms->token;
	if (ft_strcmp(str_err, "newline"))
		printf("ms: syntax error near unexpected token `%s'\n", str_err);
	while(token)
	{
		if (!ft_strcmp(token->content, "<<") && token->next && token->next->type == CMD)
			here_doc(ms, token->next->content);
		if (token->type == OPP && !is_redir(token->content))
		{
			if (token->next && token->next->type == OPP)
				return (1);
		}
		else if (token->type == OPP)
		{
			if (!token->prev)
				return (1);
			else if (token->next && token->next->type == OPP && is_redir(token->next->content))
				return (1);
		}
		token = token->next;
	}
	printf("ms: syntax error near unexpected token `%s'\n", str_err);
	return (1);
}

int	lexical_analysis(t_ms *ms)
{
	t_token	*token;
	char	*str_err;

	token = ms->token;
	while(token)
	{
		str_err = NULL;
		if (token->type == OPP && !is_redir(token->content))
		{
			if (token->next && token->next->type == OPP)
				str_err = token->next->content;
			else if (!token->next)
				str_err = "newline";
		}
		else if (token->type == OPP)
		{
			if (!token->prev)
				str_err = token->content;
			else if (token->next && token->next->type == OPP && is_redir(token->next->content))
				str_err = token->next->content;
		}
		if (str_err)
			return (lexical_error(ms, str_err));
		token = token->next;
	}
	return (0);
}
