#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
	ms->lex_err = NULL;
}

int	handle_key(t_ms *ms, char *rl)
{
	if (!ft_strcmp(rl, "clear"))
	{
		printf("\033[H\033[J");
		return (1);
	}
	if (!ft_strcmp(rl, "exit"))
	{
		clean_ms(ms, 2);
		exit (0);
	}
	return (0);
}

void	minishell(t_ms *ms)
{
	char	*rl;

	initialize_var(ms);
	rl = readline(RESET"minishell> ");
	add_history(rl);
	if (handle_key(ms, rl))
	{
		clean_ms(ms, 1);
		return ;
	}
	create_tokens(rl, ms);
	print_token(ms->token);
	if (lexical_analysis(ms))
	{
		clean_ms(ms, 2);
		return ;
	}
	parse_cmd(ms);
	print_cmd(ms->cmd);
	ms->cmd_count = ft_cmd_count(ms);
	exec_init(ms);
	clean_ms(ms, 2);
	//Builtinj
	// if (exec_builtin(ms) == 0)
	// 	exec_cmd(ms);
	free(rl);
	//exit_handler(ms, 0);
}

void	handler(int signum)
{
	if (signum == 2)
		printf("[%i]\n", signum);
}
int	main(int arc, char **arv, char **env)
{
	(void)arc;
	(void)arv;
	t_ms	ms;
	signal(SIGINT, handler);

	ms.exit_status = 42;
	ms.env = env;
	while (1)
		minishell(&ms);
	return (0);
}