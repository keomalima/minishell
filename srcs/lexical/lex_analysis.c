/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:46:49 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:46:50 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexical_error(t_ms *ms)
{
	t_token	*token;

	token = ms->token;
	if (ft_strcmp(ms->lex_err, "newline"))
		ft_print_syntax_error(ms->lex_err);
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
			if ((!token->prev || !token->next) || (token->next
					&& token->next->type == OPP
					&& is_redir(token->next->content)))
				return (1);
		}
		token = token->next;
	}
	return (ft_print_syntax_error(ms->lex_err));
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
			if (!token->prev || !token->next)
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
