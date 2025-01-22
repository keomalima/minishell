#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	t_token *list;
	t_token	*current;

	list = NULL;
	if (ac > 1)
		parse_cmd(av[1], &list);
	current = list;
	while (current)
	{
		printf("------\n");
		printf("Value [%s]\n", current->cmd);
		printf("Type [%i]\n", current->type);
		current = current->next;
	}
	return (0);
}