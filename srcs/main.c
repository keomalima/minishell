#include "minishell.h"

int	g_signal;

void	minishell(t_ms *ms)
{
	char	*rl;

	rl = ms->input_main;
	if (handle_key(rl))
		return (clean_ms(ms, 0));
	create_tokens(rl, ms);
	//print_token(ms->token);
	if (lexical_analysis(ms))
		return (clean_ms(ms, 2));
	parse_cmd(ms);
	//print_cmd(ms->cmd);
	exec_init(ms);
	clean_ms(ms, -1);
}

int	main(int arc, char **arv, char **env)
{
	t_ms	ms;

	(void)arc;
	(void)arv;
	ms.exit_status = 0;
	ms.env = ft_duplicate_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		initialize_var(&ms);
		ms.input_main = readline("minishell$ ");
		if (g_signal)
		{
			ms.exit_status = 130;
			g_signal = 0;
		}
		if (!ms.input_main)
		{
			printf("exit\n");
			exit_handler(&ms, 0);
			break ;
		}
		if (*ms.input_main)
		{
			add_history(ms.input_main);
			minishell(&ms);
		}
		free(ms.input_main);
		ms.input_main = NULL;
	}
	return (0);
}
