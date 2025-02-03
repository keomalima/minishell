#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
}

<<<<<<< HEAD
void	minishell(t_ms *ms)
=======
void	minishell(void)
>>>>>>> ae15085 (corrections on token)
{
	char	*rl;

	initialize_var(ms);
	rl = readline(RESET"minishell> ");
	add_history(rl);

<<<<<<< HEAD
	if (!ft_strcmp(rl, "clear"))
	{
		printf("\033[H\033[J");
		return ;
	}
	if (!ft_strcmp(rl, "exit"))
	{
		rl_clear_history();
		exit (0);
=======
	if (!strcmp(rl, "clear"))
	{
		printf("\033[H\033[J");
		return;
>>>>>>> 8f35b52 (cleanup version)
	}
	//Tokenization
	create_tokens(rl, ms);	//tokenization
	print_token(ms->token);	//print token

	//Lexical Analysis

	//Parsing
<<<<<<< HEAD
	parse_cmd(ms);		//parsing
	print_cmd(ms->cmd);	//print parsing

	ms->cmd_count = ft_cmd_count(ms);
=======
	parse_cmd(&ms);		//parsing
	//print_cmd(ms.cmd);	//print parsing
>>>>>>> 8f35b52 (cleanup version)

	//Builtin
	if (exec_builtin(ms) == 0)
		exec_cmd(ms);

<<<<<<< HEAD
	free(rl);
	// exit_handler(ms, 0);
=======
	//Execution
	exec_cmd(&ms);

	free(rl);
	//exit_handler(&ms, 0);
>>>>>>> 8f35b52 (cleanup version)
}

int	main(int arc, char **arv, char **env)
{
<<<<<<< HEAD

	t_ms	ms;

	(void)arc;
	(void)arv;
	ms.exit_status = 42;
	ms.env = env;

	while (1)
		minishell(&ms);
=======
	while (1)
		minishell();
>>>>>>> 8f35b52 (cleanup version)
	return (0);
}
