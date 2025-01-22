#include "../includes/minishell.h"

const char *token_type_str[] = {
    "COMMAND",
    "FILE_IN",
    "FILE_OUT",
    "FILE_OUT_APPEND",
    "PIPE",
    "ARGUMENT"
};


void define_type(t_token *new)
{
	if (new->word[0] == '<')
		new->type = FILE_IN;
	else if (new->word[0] == '>' && new->word[1] && new->word[1] == '>')
		new->type = FILE_OUT_APPEND;
	else if (new->word[0] == '>')
		new->type = FILE_OUT;
	else if (new->word[0] == '|')
		new->type = PIPE;
	else if (new->prev && new->prev->type == COMMAND)
		new->type = ARGUMENT;
	else if (new->prev && new->prev->type == ARGUMENT)
		new->type = ARGUMENT;
	else
		new->type = COMMAND;
}


void parse(t_token **token_list, char **split)
{
	t_token	*new;
	t_token	*first_token;

	int i = 0;

	while (split[i])
	{
		new = create_new_token(split[i]);
		ft_lstadd_back_ms(token_list, new);
		define_type(new);
		i++;
	}

	free(split);
	first_token = *token_list;
	while (first_token)
	{
		printf("%s	-->	%s\n", first_token->word, token_type_str[first_token->type]);
		first_token = first_token->next;
	}
}
