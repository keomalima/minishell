#include "minishell.h"

const char *token_type_str[] = {
	"START",
	"CMD",
	"OPP",
	"SQ",
	"DQ",
	"END"
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
		printf("[%s]", list->content);
		printf(purple"%s	"RESET, token_type_str[list->type]);
		list = list->next;
	}
	printf("\n------------------\n\n");
}

void print_cmd(t_cmd *list)
{
	int cmd_i;
	int	in_i;
	int	out_i;

	while (list)
	{
		cmd_i = 0;
		in_i = 0;
		out_i = 0;
		printf("cmd[%zu] : %s	|	redir : %s\n", list->cmd_size, list->cmd[cmd_i], cmd_redir[list->redir]);
		while (list->cmd[cmd_i])
		{
			printf(blue"[%s] "RESET, list->cmd[cmd_i]);
			cmd_i++;
		}
		printf("\n");
		printf(green"infile_size : %zu	"RESET, list->infile_size);
		while (list->infile[in_i])
		{
			printf(green"[%s]%d "RESET, list->infile[in_i]->name, list->infile[in_i]->is_lim);
			in_i++;
		}
		printf("\n");
		printf(yellow"outfile_size : %zu	"RESET, list->outfile_size);
		while (list->outfile[out_i])
		{
			printf(yellow"[%s]%d "RESET, list->outfile[out_i]->name, list->outfile[out_i]->type);
			out_i++;
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