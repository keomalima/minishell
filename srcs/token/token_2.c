#include "minishell.h"

static void	ft_add_to_list(t_ms *ms)
{
	t_token	*new_token;
	const char	*start_ptr;
	const char	*end_ptr;

	start_ptr = ms->lexer.str_start;
	end_ptr = ms->lexer.str_ptr;
	new_token = ft_lstnew_tk(ms, strndup(start_ptr, end_ptr - start_ptr));
	ft_lstadd_back_tk(&ms->token, new_token);
}

static void	ft_def_state(t_ms *ms)
{
	if (*ms->lexer.str_ptr == '\0')
		ms->lexer.state = END;
	else if (*ms->lexer.str_ptr == '\'')
	{
		ms->lexer.state = SQ;
		ms->lexer.s_quo_open = 1;
	}
	else if (*ms->lexer.str_ptr == '"')
	{
		ms->lexer.state = DQ;
		ms->lexer.d_quo_open = 1;
	}
	else if (ft_strchr_set("|><&", *ms->lexer.str_ptr))
		ms->lexer.state = OPP;
	else if (*ms->lexer.str_ptr != ' ')
		ms->lexer.state = CMD;
	else
		ms->lexer.str_ptr++;
	if (ms->lexer.state != START && ms->lexer.state != END)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_def_delimiter(t_ms *ms)
{
	char	str_char;

	str_char = *(ms->lexer.str_ptr);
	if (str_char == '\0')
	{
		ft_add_to_list(ms);
		ms->lexer.state = START;
	}
	else if (str_char == '\'' && ms->lexer.s_quo_open)
	{
		ms->lexer.s_quo_open = !ms->lexer.s_quo_open;
		ms->lexer.state = SQ;
	}
	else if (str_char == '"' && ms->lexer.d_quo_open)
	{
		ms->lexer.d_quo_open = !ms->lexer.d_quo_open;
		ms->lexer.state = DQ;
	}
	else if (!ms->lexer.d_quo_open && !ms->lexer.s_quo_open)
	{
		printf("Char [%c]\n", *(ms->lexer.str_ptr));
		printf("State [%u]\n", ms->lexer.state);
		if ((str_char == ' ' || ft_strchr_set("|><&", str_char))
		&& (ms->lexer.state == OPP && !ft_strchr_set("|><&", str_char)))
		{
			printf("Char [%c]\n", *(ms->lexer.str_ptr));
			ft_add_to_list(ms);
			ms->lexer.state = START;
		}
	}
}

void	create_tokens(char *input, t_ms *ms)
{
	ms->lexer.state = START;
	ms->lexer.str_ptr = input;
	ms->lexer.s_quo_open = 0;
	ms->lexer.d_quo_open = 0;
	while (ms->lexer.state != END)
	{
		//printf("Char [%c]\n", *(ms->lexer.str_ptr));
		if (ms->lexer.state == START)
			ft_def_state(ms);
		else
			ft_def_delimiter(ms);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
}