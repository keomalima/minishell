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

int	lexical_error(t_ms *ms)
{
	t_token	*token;

	token = ms->token;
	if (ft_strcmp(ms->lex_err, "newline"))
		ft_print_error("ms: syntax error near unexpected token '", ms->lex_err, "'\n");
	while (token)
	{
		if (!ft_strcmp(token->content, "<<") && token->next
			&& token->next->type == CMD)
			here_doc(ms, token->next->content);
		if (token->type == OPP && !is_redir(token->content))
		{
			if (token->next && token->next->type == OPP)
				return (1);
		}
		else if (token->type == OPP)
		{
			if (!token->prev || (token->next && token->next->type == OPP
					&& is_redir(token->next->content)))
				return (1);
		}
		token = token->next;
	}
	ft_print_error("ms: syntax error near unexpected token '", ms->lex_err, "'\n");
	return (1);
}

static	int	is_valid_operand(t_token *token)
{
	int	i;
	const char	*valid_ops[] = {">", ">>", "<", "<<", "|", NULL};

	i = 0;
	if (token->type != OPP)
		return (0);
	while (valid_ops[i])
	{
		if (!ft_strcmp(token->content, valid_ops[i]))
			return (0);
		i++;
	}
	ft_print_error("ms: not a valid operand: ", token->content, NULL);
	ft_printf("\n");
	return (1);
}

static int	check_token(t_ms *ms, t_token *token)
{
	while (token)
	{
		if (token->type == OPP && !is_redir(token->content))
		{
			if (token->next && token->next->type == OPP)
				ms->lex_err = token->next->content;
			else if (!token->next)
				ms->lex_err = "newline";
		}
		else if (token->type == OPP)
		{
			if (!token->prev)
				ms->lex_err = token->content;
			else if (token->next && token->next->type == OPP
				&& is_redir(token->next->content))
				ms->lex_err = token->next->content;
		}
		if (ms->lex_err)
			return (lexical_error(ms));
		else if (is_valid_operand(token))
			return (1);
		token = token->next;
	}
	return (0);
}

int	lexical_analysis(t_ms *ms)
{
	t_token	*token;

	token = ms->token;
	if (ms->lexer.s_quo_open || ms->lexer.d_quo_open)
		return (1);
	if (check_token(ms, token))
		return (1);
	return (0);
}