#include "minishell.h"

static void	ft_define_state(t_ms *ms)
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
		ms->lexer.str_start = ms->lexer.str_ptr;
	}
	else if (ms->lexer.state == CMD || ms->lexer.state == OPP)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_token_checker(t_ms *ms)
{
	t_type	state;

	state = ms->lexer.state;
	if (*ms->lexer.str_ptr == '"' || *ms->lexer.str_ptr == '\'')
		ms->lexer.state = START;
	else if ((*ms->lexer.str_ptr == ' ' || *ms->lexer.str_ptr == '\0'))
	{
		if (!ms->lexer.quote_open)
			ft_lstadd_back_tk(&ms->token, ft_lstnew_tk(ms, ft_strndup_tk(ms)));
		if (!ms->lexer.quote_open || *ms->lexer.str_ptr == '\0')
			ms->lexer.state = START;
	}
	else if ((!ft_strchr_set("|><&", *ms->lexer.str_ptr) && state == OPP)
		|| (is_val_opp(ms->lexer.str_start, ms->lexer.str_ptr) && state == OPP)
		|| (state == CMD && ft_strchr_set("|><&", *ms->lexer.str_ptr)))
	{
		ft_lstadd_back_tk(&ms->token, ft_lstnew_tk(ms, ft_strndup_tk(ms)));
		ms->lexer.state = START;
	}
}

static void	ft_token_checker_quote(t_ms *ms)
{
	ms->lexer.quote_open = !ms->lexer.quote_open;
	if (*(ms->lexer.str_ptr + 1) == '\'' || *(ms->lexer.str_ptr + 1) == '"')
	{
		ms->lexer.state = DQ;
		if (*(ms->lexer.str_ptr + 1) == '\'')
			ms->lexer.state = SQ;
	}
	else if (!ms->lexer.quote_open && (
			*(ms->lexer.str_ptr + 1) == ' '
			|| *(ms->lexer.str_ptr + 1) == '\0'
			|| ft_strchr_set("|><&", *(ms->lexer.str_ptr + 1))))
	{
		ft_lstadd_back_tk(&ms->token, ft_lstnew_tk(ms, ft_strndup_tk(ms)));
		ms->lexer.state = START;
		ms->lexer.str_ptr++;
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
		else if ((*ms->lexer.str_ptr == '\'' && ms->lexer.state != DQ)
			|| (*ms->lexer.str_ptr == '"' && ms->lexer.state != SQ))
			ft_token_checker_quote(ms);
		else
			ft_token_checker(ms);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
	if (ms->lexer.quote_open)
	{
		printf("Unclosed quote\n");
		exit_handler(ms, 1);
	}
}
