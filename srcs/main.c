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
		if (ms->mod_env == 1)
			free_split(ms->env);
		clear_history();
		exit (0);
	}
	//Tokenization
	create_tokens(rl, ms);	//tokenization
	// print_token(ms->token);	//print token

	//Lexical Analysis
	lexical_analysis(ms);

	//Parsing
	parse_cmd(ms);		//parsing
	// print_cmd(ms->cmd);	//print parsing

	ms->cmd_count = ft_cmd_count(ms);

	//Builtin
	if (exec_builtin(ms) == 0)
		exec_cmd(ms);

	free(rl);
	clean_ms(ms, 0);
	// exit_handler(ms, 0);
}

void	minishell(t_ms *ms, char *rl)
{
	initialize_var(ms);
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
}

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int	main(int arc, char **arv, char **env)
{
	(void)arc;
	(void)arv;
	t_ms	ms;
	char *input;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ms.exit_status = 42;
	ms.env = env;
	ms.mod_env = 0;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			minishell(&ms, input);
		}
		free(input);
	}
	return (0);
}
