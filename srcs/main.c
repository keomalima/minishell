#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
}

void	minishell(void)
{
	t_ms	ms;
	char	*rl;

	initialize_var(&ms);
	rl = readline("minishell> ");

	if (!strcmp(rl, "clear"))
	{
		printf("\033[H\033[J");
		return;
	}
	//Tokenization
	create_tokens(rl, &ms);	//tokenization
	print_token(ms.token);	//print token

	//Lexical Analysis

	//Parsing
	parse_cmd(&ms);		//parsing
	//print_cmd(ms.cmd);	//print parsing

	//Builtin
	exec_builtin(&ms);

	//Execution
	exec_cmd(&ms);

	free(rl);
	//exit_handler(&ms, 0);
}

int	main(void)
{
	while (1)
		minishell();
	return (0);
}
