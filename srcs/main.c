#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
}

int	main(void)
{
	t_ms	ms;
	//t_token	*current;
	char	*rl;

	initialize_var(&ms);
	rl = readline("minishell> ");
	create_tokens(rl, &ms);
	parse_cmd(&ms);
	exec_cmd(&ms);
	//print_cmd(ms.cmd);
	//exit_handler(&ms, 0);
	free(rl);
	return (0);
}
