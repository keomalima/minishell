#include "minishell.h"

int	handle_key(char *rl)
{
	if (ft_is_special_cmd(rl, "clear"))
	{
		printf("\033[H\033[J");
		return (1);
	}
	return (0);
}

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
	ms->lex_err = NULL;
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}