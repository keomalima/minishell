#include "minishell.h"

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
	//print_cmd(ms->cmd);
	exec_init(ms);
	clean_ms(ms, -1);
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
	return (0);
}