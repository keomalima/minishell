#include "minishell.h"

void	ft_define_state(t_ms *ms)
{
	if (*ms->lexer.str_ptr == '\0')
		ms->lexer.state = END;
	else if (*ms->lexer.str_ptr == '\'')
		ms->lexer.state = SQ;
	else if (*ms->lexer.str_ptr == '"')
		ms->lexer.state = DQ;
	else if (ft_strchr_set("|><&", *ms->lexer.str_ptr))
		ms->lexer.state = OPP;
	else if (*ms->lexer.str_ptr != ' ')
		ms->lexer.state = CMD;
	else
		ms->lexer.str_ptr++;
	if (ms->lexer.state == SQ || ms->lexer.state == DQ)
	{
		ms->lexer.quote_open = 1;
		ms->lexer.str_start = ms->lexer.str_ptr + 1;
	}
	else if (ms->lexer.state == CMD || ms->lexer.state == OPP)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_token_checker(t_ms *ms)
{
	if (*ms->lexer.str_ptr == '\'')
	{
		if (ms->lexer.state != DQ)
			ms->lexer.quote_open = !ms->lexer.quote_open;
		ms->lexer.state = SQ;
	}
	else if (*ms->lexer.str_ptr == '"')
	{
		if (ms->lexer.state != SQ)
			ms->lexer.quote_open = !ms->lexer.quote_open;
		ms->lexer.state = DQ;
	}
	else if (ms->lexer.state == OPP
		&& !ft_strchr_set("|><&", *ms->lexer.str_ptr))
	{
		ft_lstadd_back_tk(&ms->token, ft_lstnew_tk(ms, ft_strndup_tk(ms)));
		ms->lexer.state = START;
	}
	else if ((*ms->lexer.str_ptr == ' '
			|| *ms->lexer.str_ptr == '\0') && !ms->lexer.quote_open)
	{
		ft_lstadd_back_tk(&ms->token, ft_lstnew_tk(ms, ft_strndup_tk(ms)));
		ms->lexer.state = START;
	}
}

void	create_tokens(char *input, t_ms *ms)
{
	ms->lexer.state = START;
	ms->lexer.str_ptr = input;
	ms->lexer.quote_open = 0;
	while (ms->lexer.state != END)
	{
		if (ms->lexer.state == START)
			ft_define_state(ms);
		else
			ft_token_checker(ms);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
}
