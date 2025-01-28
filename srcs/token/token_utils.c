#include "minishell.h"

char	*ft_strchr_set(char *set, int c)
{
	while (*set)
	{
		if (c == *set)
			return (set);
		set++;
	}
	return (NULL);
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

char	*ft_strndup_ms(t_ms *ms)
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
	while ((ms->lexer.str_start + i) != ms->lexer.str_ptr)
	{
		if (ft_define_state(ms->lexer.str_start[i]) != ms->lexer.state)
			str[j++] = ms->lexer.str_start[i];
		i++;
	}
	return (str);
}

char	*type_to_string(t_type type)
{
	switch (type)
	{
		case START:	return "START";
		case END:	return "END";
		case SQ:	return "IN_SINGLE_QUOTE";
		case DQ:	return "IN_DOUBLE_QUOTE";
		case OPP:	return "IN_OPERATOR";
		case CMD:	return "IN_COMMAND";
		default:	return "UNKNOWN";
	}
}