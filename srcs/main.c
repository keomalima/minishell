#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
}

int main (int arc, char **arv)
{
	(void)arc;

	char **split;
	split = ft_split(arv[1], ' ');
	int i = 0;
	while (split[i])
	{
		printf("%d --> |%s|\n", i, split[i]);
		i++;
	}
	printf("------------------\n\n");

	t_token	*token_list;
	token_list = NULL;
	parse(&token_list, split);

	return (0);
}
