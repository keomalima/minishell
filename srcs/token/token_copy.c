#include "minishell.h"

static t_type	ft_define_state(t_ms *ms)
{
	if (*ms->lexer.str_ptr == '\'')
		ms->lexer.state = SQ;
	else if (*ms->lexer.str_ptr == '"')
		ms->lexer.state = DQ;
	else
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
	while ((ms->lexer.str_start + i) != ms->lexer.str_ptr)
	{
		if (ft_define_state(ms->lexer.str_start[i]) != ms->lexer.state)
			len++;
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
			ft_define_state(ms);
		else
		{
			if (*(ms->lexer.str_ptr + 1) == '\'' && ms->lexer.state == SQ)
				ms->lexer.state = START;
			else if (*(ms->lexer.str_ptr + 1) == '"' && ms->lexer.state == DQ)
				ms->lexer.state = START;
		}
		if (ft_define_state(ms->lexer.str_start[i]) != ms->lexer.state && ms->lexer.state != START)
			str[j++] = ms->lexer.str_start[i];
		i++;
	}
	return (str);
}
