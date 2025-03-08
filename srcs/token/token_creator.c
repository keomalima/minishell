#include "minishell.h"

static t_token	*ft_tknlast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_add_to_list(t_ms *ms)
{
	t_token		*new_token;
	t_token		*last_list;
	char		*content;
	const char	*start_ptr;
	const char	*end_ptr;

	start_ptr = ms->lexer.str_start;
	end_ptr = ms->lexer.str_ptr;
	new_token = NULL;
	content = ft_strndup(start_ptr, end_ptr - start_ptr);
	if (ms->lexer.state == CMD && ft_count_alpha_exp(content))
		ms->lexer.state = EXP;
	last_list = ft_tknlast(ms->token);
	last_list = ft_tknlast(ms->token);
	if (!(last_list && last_list->type == OPP
		&& !ft_strcmp(last_list->content, "<<")))
		content = ft_translate_file(content, ms);
	if (content)
	{
		new_token = ft_lstnew_tk(ms, content);
		ft_lstadd_back_tk(&ms->token, new_token);
	}
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
	else if (ft_strchr_set("|><&", *ms->lexer.str_ptr))
		ms->lexer.state = OPP;
	else if (!ft_isspace(*ms->lexer.str_ptr))
		ms->lexer.state = CMD;
	else
		ms->lexer.str_ptr++;
	if (ms->lexer.state != START && ms->lexer.state != END)
		ms->lexer.str_start = ms->lexer.str_ptr;
}

static void	ft_def_delimiter(t_ms *ms, char str_char)
{
	if (str_char == '\0')
		ft_add_to_list(ms);
	else if (str_char == '\'')
	{
		if (ms->lexer.state != DQ)
			ms->lexer.state = SQ;
		if (!ms->lexer.d_quo_open)
			ms->lexer.s_quo_open = !ms->lexer.s_quo_open;
	}
	else if (str_char == '"')
	{
		if (ms->lexer.state == OPP && !ms->lexer.d_quo_open)
			ft_add_to_list(ms);
		else
		{
			if (ms->lexer.state != SQ)
				ms->lexer.state = DQ;
			if (!ms->lexer.s_quo_open)
				ms->lexer.d_quo_open = !ms->lexer.d_quo_open;
		}
	}
	else if (!ms->lexer.d_quo_open && !ms->lexer.s_quo_open)
	{
		if ((ms->lexer.state == OPP &&
			is_val_opp(ms->lexer.str_start, ms->lexer.str_ptr)))
			ft_add_to_list(ms);
		else if (ft_isspace(str_char) || (ms->lexer.state != OPP
			&& ft_strchr_set("|><&", str_char)))
			ft_add_to_list(ms);
	}
}

void	create_tokens(char *input, t_ms *ms)
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
			ft_def_delimiter(ms, str_char);
		if (ms->lexer.state != START && ms->lexer.state != END)
			ms->lexer.str_ptr++;
	}
	if (ms->lexer.s_quo_open || ms->lexer.d_quo_open)
	{
		ft_print_error("Unclosed quote\n", NULL, NULL);
	}
}
