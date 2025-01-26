#include "../includes/minishell.h"

const char *type_to_string(t_type type)
{
	switch (type)
	{
		case START:           return "START";
		case END:             return "END";
		case IN_SINGLE_QUOTE: return "IN_SINGLE_QUOTE";
		case IN_DOUBLE_QUOTE: return "IN_DOUBLE_QUOTE";
		case IN_OPERATOR:     return "IN_OPERATOR";
		case IN_COMMAND:      return "IN_COMMAND";
		default:              return "UNKNOWN";
	}
}

int	main(void)
{
	t_token *list;
	t_token	*current;
	char *rl;

	list = NULL;
	rl = readline("Prompt > ");
	finite_state_machine(rl, &list);

	current = list;
	while (current)
	{
		printf("------\n");
		printf("Value [%s] - ", current->cmd);
		printf("Type [%s]\n", type_to_string(current->type));
		current = current->next;
	}
	return (0);
}