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
	if (ft_is_special_cmd(rl, "clear"))
	{
		printf("\033[H\033[J");
		return (1);
	}
	if (ft_is_special_cmd(rl, "exit"))
	{
		free_split(ms->env);
		clean_ms(ms, 2);
		exit (0);
	}
	return (0);
}

void	minishell(t_ms *ms, char *rl)
{
	initialize_var(ms);
	if (handle_key(ms, rl))
	{
		clean_ms(ms, 0);
		return ;
	}
	create_tokens(rl, ms);
	// print_token(ms->token);
	if (lexical_analysis(ms))
	{
		clean_ms(ms, 2);
		return ;
	}
	parse_cmd(ms);
	// print_cmd(ms->cmd);
	ms->cmd_count = ft_cmd_count(ms);
	if (solo_builtin(ms) == 0)
		exec_init(ms);
	clean_ms(ms, -1);
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
	ms.exit_status = 0;
	ms.env = ft_duplicate_env(&ms, env);
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

	// (void)env;
	// input = readline("minishell$ ");
	// input = ft_translate(input, &ms);
	printf(red"translate : %s\n"RESET, input);


	return (0);
}