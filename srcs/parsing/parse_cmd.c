#include "minishell.h"

static void	ft_add_to_list(t_ms *ms, t_cmd *new, t_index *index)
{
	const char	*start_ptr;
	const char	*end_ptr;

	start_ptr = ms->lexer.str_start;
	end_ptr = ms->lexer.str_ptr;
	new->cmd[index->cmd_i++] = ft_strndup(start_ptr, end_ptr - start_ptr);
	ms->lexer.state = START;
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
	else if (!ft_isspace(*ms->lexer.str_ptr))
		ms->lexer.state = CMD;
	else
		ms->lexer.str_ptr++;
	if (ms->lexer.state != START && ms->lexer.state != END)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_def_delimiter(t_ms *ms, char str_char, t_cmd *new, t_index *index)
{
	if (str_char == '\0')
		ft_add_to_list(ms, new, index);
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
			ft_add_to_list(ms, new, index);
	}
}

void	ft_stract_word(char *input, t_ms *ms, t_cmd *new, t_index *index)
{
	char	str_char;

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
			ft_def_delimiter(ms, str_char, new, index);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
}