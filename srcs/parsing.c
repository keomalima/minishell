#include "../includes/minishell.h"

const char *token_type_str[] = {
    RED"COMMAND"RESET,
    YELLOW"FILE_IN"RESET,
    YELLOW"FILE_OUT"RESET,
    YELLOW"FILE_OUT_APPEND"RESET,
	yellow"FILE_NAME"RESET,
    BLUE"PIPE"RESET,
    red"ARGUMENT"RESET,
	GREEN"PATH"RESET
};

void define_type(t_token *node)
{
	if (node->word[0] == '.' || node->word[0] == '/')
		node->type = PATH;
	else if (node->word[0] == '<')
		node->type = FILE_IN;
	else if (node->word[0] == '>' && node->word[1] && node->word[1] == '>')
		node->type = FILE_OUT_APPEND;
	else if (node->word[0] == '>')
		node->type = FILE_OUT;
	else if (node->word[0] == '|')
		node->type = PIPE;
	else if (node->prev && (ft_strcmp(node->prev->word, "<") == 0 || ft_strcmp(node->prev->word, ">") == 0 || ft_strcmp(node->prev->word, ">>") == 0))
		node->type = FILE_NAME;
	else if (node->prev && node->prev->type == COMMAND)
		node->type = ARGUMENT;
	else if (node->prev && node->prev->type == ARGUMENT)
		node->type = ARGUMENT;
	else
		node->type = COMMAND;
}


void parse(t_token **token_list, char **split)
{
	int		i;
	t_token	*new;
	t_token	*current;

	i = 0;
	while (split[i])
	{
		new = create_new_token(split[i]);
		if (!new)
		{
			ft_lstclear_ms(token_list, &del_content);
			return;
		}
		ft_lstadd_back_ms(token_list, new);
		define_type(new);
		i++;
	}
	free(split);
	current = *token_list;
	while (current)
	{
		printf("%s	-->	%s\n", current->word, token_type_str[current->type]);
		current = current->next;
	}
}
