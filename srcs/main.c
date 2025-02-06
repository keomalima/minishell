#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
}

void	minishell(t_ms *ms)
{
	char	*rl;

	initialize_var(ms);
	rl = readline(RESET"minishell> ");
	add_history(rl);

	if (!ft_strcmp(rl, "clear"))
	{
		printf("\033[H\033[J");
		return ;
	}
	if (!ft_strcmp(rl, "exit"))
	{
		rl_clear_history();
		exit (0);
	}
	//Tokenization
	create_tokens(rl, ms);	//tokenization
	print_token(ms->token);	//print token

	//Lexical Analysis
	if (lexical_analysis(ms))
	{
		clean_ms(ms, 2);
		return ;
	}

	//Parsing
	parse_cmd(ms);		//parsing
	print_cmd(ms->cmd);	//print parsing

	ms->cmd_count = ft_cmd_count(ms);
	exec_cmd(ms);
	//Builtin
	// if (exec_builtin(ms) == 0)
	// 	exec_cmd(ms);

	free(rl);
	// exit_handler(ms, 0);
}

int	main(int arc, char **arv, char **env)
{
	t_ms	ms;

	(void)arc;
	(void)arv;
	ms.exit_status = 42;
	ms.env = env;

	// char *arg[] = {NULL, NULL, NULL};
	// if (execve(arg[0], arg, NULL) < 0)
	// 	perror("Execve error ");
	while (1)
		minishell(&ms);
	return (0);
}