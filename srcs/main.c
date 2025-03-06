#include "minishell.h"

int	g_signal;

void	minishell(t_ms *ms, char *rl)
{
	initialize_var(ms);
	if (handle_key(rl))
		return (clean_ms(ms, 0));
	create_tokens(rl, ms);
	//print_token(ms->token);
	if (lexical_analysis(ms))
		return (clean_ms(ms, 2));
	parse_cmd(ms);
	print_cmd(ms->cmd);
	exec_init(ms);
	clean_ms(ms, -1);
}

int	main(int arc, char **arv, char **env)
{
	t_ms	ms;
	char	*input;

	(void)arc;
	(void)arv;
	ms.exit_status = 0;
	ms.env = ft_duplicate_env(&ms, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		input = readline("minishell$ ");
		if (g_signal)
		{
			ms.exit_status = 130;
			g_signal = 0;
		}
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			minishell(&ms, input);
		}
		free(input);
	}
	return (0);
}
