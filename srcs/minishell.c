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

void	ft_token_in_cmd(char ch, const char **token_start, t_type *state, const char **ptr)
{
	if (isspace(ch) || ch == '\0')
	{
		printf("Command/Arg: %.*s\n", (int)(*ptr - *token_start), *token_start);
		*state = START;
	}
}

void	ft_token_in_opp(char ch, const char **token_start, t_type *state, const char **ptr)
{
	if (!strchr("|><&", ch))
	{
		printf("Operator: %.*s\n", (int)(*ptr - *token_start), *token_start);
		*state = START;
	}
}

void	ft_token_in_dquote(char ch, const char **token_start, t_type *state, const char **ptr)
{
	if (ch == '"')
	{
		printf("Double-quoted: %.*s\n", (int)(*ptr - *token_start), *token_start);
		*state = START;
		(*ptr)++;
	}
}

void	ft_token_in_squote(char ch, const char **token_start, t_type *state, const char **ptr)
{
	if (ch == '\'')
	{
		printf("Single-quoted: %.*s\n", (int)(*ptr - *token_start), *token_start);
		*state = START;
		(*ptr)++;
	}
}

void tokenize(const char *input)
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
		else if (state == IN_COMMAND)
			ft_token_in_cmd(*ptr, &token_start, &state, &ptr);
		else if (state == IN_OPERATOR)
			ft_token_in_opp(*ptr, &token_start, &state, &ptr);
		else if (state == IN_SINGLE_QUOTE)
			ft_token_in_squote(*ptr, &token_start, &state, &ptr);
		else if (state == IN_DOUBLE_QUOTE)
			ft_token_in_dquote(*ptr, &token_start, &state, &ptr);
		if (state != START)
			ptr++;
	}
}

void	finite_state_machine(char *input)
{
	printf("Tokenizing: \"%s\"\n", input);
	tokenize(input);
}
