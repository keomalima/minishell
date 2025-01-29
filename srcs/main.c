#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
}

int	main(void)
{
	t_ms	ms;
	char	*rl;

	initialize_var(&ms);
	rl = readline("minishell> ");
	create_tokens(rl, &ms);

	//Parsing
	parse_cmd(&ms);		//parsing
	print_cmd(ms.cmd);	//print parsing

	exit_handler(&ms, 0);
	free(rl);
	return (0);
}
