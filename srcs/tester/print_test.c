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
	"IN",
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

void print_cmd(t_cmd *current)
{
	int	cmd_i;
	int	in_i;
	t_cmd	*list;

	list = current;
	while (list)
	{
		cmd_i = 0;
		in_i = 0;
		printf("cmd[%zu] : %s    |    redir : %s\n", list->cmd_size, list->cmd[cmd_i], cmd_redir[list->redir]);
		while (list->cmd[cmd_i])
		{
			printf(blue"[%s] "RESET, list->cmd[cmd_i]);
			cmd_i++;
		}
		printf("\n");
		printf(green"file_size : %zu    "RESET, list->files_size);
		while (list->files[in_i])
		{
			printf(green"[%s]%d - Type [%d] "RESET, list->files[in_i]->name, list->files[in_i]->is_lim, list->files[in_i]->type);
			in_i++;
		}
		printf("\n");
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

void	ft_print_res_export(t_var **env_var)
{
	size_t	i;

	i = 0;
	while (env_var[i])
	{
		printf("[%zu]	name [%s]		value [%s]\n", i, env_var[i]->name, env_var[i]->value);
		i++;
	}
}