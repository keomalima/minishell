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

	/* //Tokenization
	create_tokens(rl, &ms);	//tokenization
	print_token(ms.token);	//print token

	//Lexical Analysis

	//Parsing
	parse_cmd(&ms);		//parsing
	print_cmd(ms.cmd);	//print parsing */

	//Expanser
	if (ft_strchr(rl, '$'))
	{
		char	*expansed;
		expansed = expanse_var(rl);
		printf("expanser : [%s]\n", expansed);
	}


	exit_handler(&ms, 0);
	free(rl);
	return (0);
}
