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

void print_list(t_token *list)
{
	while (list)
	{
		printf("%s	-->	%s\n", list->word, token_type_str[list->type]);
		list = list->next;
	}
	printf("\n------------------\n\n");
}

void print_split(char **split)
{
	int i;
	
	i = 0;
	while (split[i])
	{
		printf("%d --> |%s|\n", i, split[i]);
		i++;
	}
	printf("\n------------------\n\n");
}