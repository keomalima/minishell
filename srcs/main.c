#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
}

int	main(void)
{
	t_ms	ms;
	char	*rl;

	initialize_var(&ms);
	rl = readline("minishell> ");
	create_tokens(rl, &ms);
	//Parsing ft
	parsing_token(&ms);
	exit_handler(&ms, 0);
	free(rl);
	return (0);
}