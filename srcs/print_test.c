#include "../includes/minishell.h"

const char *token_type_str[] = {
    RED"COMMAND"RESET,
    YELLOW"FILE_IN"RESET,
    YELLOW"FILE_OUT"RESET,
    YELLOW"FILE_OUT_APPEND"RESET,
	yellow"FILE_NAME"RESET,
    BLUE"PIPE"RESET,
    red"ARGUMENT"RESET,
	GREEN"PATH"RESET,
	PURPLE"OPERATOR"RESET
};

const char *cmd_redir[] = {
	"UNDEFINED",
	"OUT_TRUNC",
	"OUT_APPEND",
	"PIPE"
};

void print_token(t_token *list)
{
	while (list)
	{
		printf("%s	", list->content);
		list = list->next;
	}
	printf("\n------------------\n\n");
}

void print_cmd(t_cmd *list)
{
	int i;

	while (list)
	{
		i = 0;
		printf("cmd[%d] : %s	|	infile : %s	|	outfile	: %s	|	redir ; %s\n", list->cmd_size, list->cmd[i], list->infile, list->outfile, cmd_redir[list->redir]);
		while (list->cmd[i])
		{
			printf(blue"[%s] "RESET, list->cmd[i]);
			i++;
		}
		printf("\n\n");
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