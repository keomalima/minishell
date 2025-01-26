#include "../includes/minishell.h"

void	ft_token_start(char ch, const char **token_start, t_type *state, const char **ptr)
{
	if (ch == '\0')
		*state = END;
	else if (ch == '\'')
		*state = IN_SINGLE_QUOTE;
	else if (ch == '"')
		*state = IN_DOUBLE_QUOTE;
	else if (strchr("|><&", ch))
		*state = IN_OPERATOR;
	else if (!isspace(ch))
		*state = IN_COMMAND;
	else
		(*ptr)++;
	if (*state == IN_SINGLE_QUOTE || *state == IN_DOUBLE_QUOTE)
		*token_start = *ptr + 1;
	else if (*state == IN_COMMAND || *state == IN_OPERATOR)
		*token_start = *ptr;
}

void	ft_token_checker(char ch, const char **token_start, t_type *state, const char **ptr, t_token **list)
{
	if (*state == IN_SINGLE_QUOTE && ch == '\'')
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(strndup(*token_start, (*ptr - *token_start)) , IN_SINGLE_QUOTE));
		*state = START;
		(*ptr)++;
	}
	else if (*state == IN_DOUBLE_QUOTE && ch == '"')
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(strndup(*token_start, (*ptr - *token_start)) , IN_DOUBLE_QUOTE));
		*state = START;
		(*ptr)++;
	}
	else if (*state == IN_COMMAND && (isspace(ch) || ch == '\0'))
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(strndup(*token_start, (*ptr - *token_start)) , IN_COMMAND));
		*state = START;
	}
	else if (*state == IN_OPERATOR && !strchr("|><&", ch))
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(strndup(*token_start, (*ptr - *token_start)) , IN_OPERATOR));
		*state = START;
	}
}

void	finite_state_machine(char *input, t_token **list)
{
	t_type		state;
	const char *token_start;
	const char	*ptr;

	token_start = NULL;
	state = START;
	ptr = input;
	while (state != END)
	{
		if (state == START)
			ft_token_start(*ptr, &token_start, &state, &ptr);
		else
			ft_token_checker(*ptr, &token_start, &state, &ptr, list);
		if (state != START)
			ptr++;
	}
}
