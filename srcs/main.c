#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
}


int main (int arc, char **arv)
{
	char	**split;
	char	*rl;

	(void)arc;
	(void)arv;
	print_split(arv + 1);
	rl = readline("Prompt > ");
	split = ft_split_ms(rl);
	if (!split)
		return (1);
	print_split(split);

	// t_token	*token_list;
	// token_list = NULL;
	// parse_lex(&token_list, split);


	return (0);
}
