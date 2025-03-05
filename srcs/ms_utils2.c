#include "minishell.h"

void	ft_print_error(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
}

int	handle_key(char *rl)
{
	if (ft_is_special_cmd(rl, "clear"))
	{
		printf("\033[H\033[J");
		return (1);
	}
	else if(ft_is_special_cmd(rl, "!") || ft_is_special_cmd(rl, ":")
		|| ft_is_special_cmd(rl, "~"))
		return (1);
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
	g_signal = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_is_only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}
