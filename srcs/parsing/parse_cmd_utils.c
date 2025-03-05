#include "minishell.h"

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
	else if (!ft_isspace(*ms->lexer.str_ptr))
		ms->lexer.state = CMD;
	else
		ms->lexer.str_ptr++;
	if (ms->lexer.state != START && ms->lexer.state != END)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_def_delimiter(t_ms *ms, char str_char, int *word)
{
	if (str_char == '\0')
	{
		(*word)++;
		ms->lexer.state = START;
	}
	else if (str_char == '\'')
	{
		if (ms->lexer.state != DQ)
			ms->lexer.state = SQ;
		ms->lexer.s_quo_open = !ms->lexer.s_quo_open;
	}
	else if (str_char == '"')
	{
		if (ms->lexer.state != SQ)
			ms->lexer.state = DQ;
		ms->lexer.d_quo_open = !ms->lexer.d_quo_open;
	}
	else if (!ms->lexer.d_quo_open && !ms->lexer.s_quo_open)
	{
		if (ft_isspace(str_char))
		{
			(*word)++;
			ms->lexer.state = START;
		}
	}
}

int	ft_count_words(char *input, t_ms *ms)
{
	char	str_char;
	int		word_len;

	word_len = 0;
	ms->lexer.state = START;
	ms->lexer.str_ptr = input;
	ms->lexer.s_quo_open = 0;
	ms->lexer.d_quo_open = 0;
	while (ms->lexer.state != END)
	{
		str_char = *(ms->lexer.str_ptr);
		if (ms->lexer.state == START)
			ft_def_state(ms);
		else
			ft_def_delimiter(ms, str_char, &word_len);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
	return (word_len);
}
