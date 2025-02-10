#include "minishell.h"

static void	ft_set_state(char c, t_ms *ms)
{
	if (c == '\'')
		ms->lexer.state = SQ;
	else if (c == '"')
		ms->lexer.state = DQ;
	else if (ft_strchr_set("|><&", c))
		ms->lexer.state = OPP;
	else if (c != ' ')
		ms->lexer.state = CMD;
}

static t_type	ft_define_state(char c)
{
	if (c == '"')
		return (DQ);
	if (c == '\'')
		return (SQ);
	return (START);
}

size_t	ft_strlen_state(t_ms *ms)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	ms->lexer.state = START;
	while ((ms->lexer.str_start + i) != ms->lexer.str_ptr)
	{
		if (ms->lexer.state == START)
			ft_set_state(ms->lexer.str_start[i], ms);
		else
		{
			if (*(ms->lexer.str_start + i) == '\'' && ms->lexer.state == SQ)
				ms->lexer.state = START;
			else if (*(ms->lexer.str_start + i) == '"' && ms->lexer.state == DQ)
				ms->lexer.state = START;
		}
		if (ft_define_state(ms->lexer.str_start[i]) != ms->lexer.state && ms->lexer.state != START)
			len++;
		if (ms->lexer.state != START)
			i++;
	}
	return (len);
}


char	*ft_strndup_tk(t_ms *ms)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!ms->lexer.str_start || !ms->lexer.str_ptr)
		exit_handler(ms, 1);
	len = ft_strlen_state(ms);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		exit_handler(ms, 1);
	i = 0;
	j = 0;
	ms->lexer.state = START;
	while ((ms->lexer.str_start + i) != ms->lexer.str_ptr)
	{
		if (ms->lexer.state == START)
			ft_set_state(ms->lexer.str_start[i], ms);
		else
		{
			if (*(ms->lexer.str_start + i) == '\'' && ms->lexer.state != DQ)
				ms->lexer.state = START;
			else if (*(ms->lexer.str_start + i) == '"' && ms->lexer.state != SQ)
				ms->lexer.state = START;
		}
		if (ft_define_state(ms->lexer.str_start[i]) != ms->lexer.state && ms->lexer.state != START)
			str[j++] = ms->lexer.str_start[i];
		if (ms->lexer.state != START)
			i++;
	}
	return (str);
}
