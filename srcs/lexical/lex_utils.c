/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:46:54 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:46:55 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_syntax_error(char *s)
{
	ft_print_error("ms: syntax error near unexpected token '", s, "'\n");
	return (1);
}

size_t	is_redir(const char *content)
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

int	is_valid_operand(t_token *token)
{
	int			i;
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
	ft_print_error("ms: not a valid operand: ", token->content, "\n");
	return (1);
}
