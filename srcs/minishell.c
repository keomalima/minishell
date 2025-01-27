#include "../includes/minishell.h"

void	ft_token_start(t_lexer *lexer)
{
	if (*lexer->str_ptr == '\0')
		lexer->state = END;
	else if (*lexer->str_ptr == '\'')
		lexer->state = IN_SINGLE_QUOTE;
	else if (*lexer->str_ptr == '"')
		lexer->state = IN_DOUBLE_QUOTE;
	else if (strchr("|><&", *lexer->str_ptr))
		lexer->state = IN_OPERATOR;
	else if (!isspace(*lexer->str_ptr))
		lexer->state = IN_COMMAND;
	else
		(lexer->str_ptr)++;
	if (lexer->state == IN_SINGLE_QUOTE || lexer->state == IN_DOUBLE_QUOTE)
	{
		lexer->is_quote_open = 1;
		lexer->token_start = lexer->str_ptr + 1;
	}
	else if (lexer->state == IN_COMMAND || lexer->state == IN_OPERATOR)
		lexer->token_start = lexer->str_ptr;
}

void	ft_token_checker(t_lexer *lexer, t_token **list)
{
	if (lexer->state == IN_SINGLE_QUOTE && *lexer->str_ptr == '\'')
		lexer->is_quote_open = !lexer->is_quote_open;
	else if (lexer->state == IN_DOUBLE_QUOTE && *lexer->str_ptr == '"')
		lexer->is_quote_open = !lexer->is_quote_open;
	else if (lexer->state == IN_OPERATOR && !strchr("|><&", *lexer->str_ptr))
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(ft_strndup_ms(lexer->token_start, lexer->str_ptr, lexer->state), lexer->state));
		lexer->state = START;
	}
	if ((*lexer->str_ptr == ' ' || *lexer->str_ptr == '\0') && !lexer->is_quote_open)
	{
		ft_lstadd_back_ms(list, ft_lstnew_ms(ft_strndup_ms(lexer->token_start, lexer->str_ptr, lexer->state), lexer->state));
		lexer->state = START;
	}
}

void	finite_state_machine(char *input, t_token **list)
{
	t_lexer		lexer;

	lexer.token_start = NULL;
	lexer.state = START;
	lexer.str_ptr = input;
	lexer.is_quote_open = 0;
	while (lexer.state != END)
	{
		if (lexer.state == START)
			ft_token_start(&lexer);
		else
			ft_token_checker(&lexer, list);
		if (lexer.state != START)
			lexer.str_ptr++;
	}
	if (lexer.is_quote_open)
		printf("Error: Quote open\n");
}
