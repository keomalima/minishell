#include "minishell.h"

int	check_interupt(void)
{
	return (0);
}

void	sigint_here_doc(int sig)
{
	g_signal = sig;
	rl_done = 1;
}

void	exec_here_doc(t_ms *ms, char *limiter, int i)
{
	char	*str;

	rl_event_hook = check_interupt;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_here_doc);
	close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][1]);
	close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
	if (pipe(ms->exec->pipe_fd[(i + 1) % 2]) < 0)
		exit_handler(ms, 1);
	while (1)
	{
		str = readline("> ");
		if (g_signal != 0)
			return ;
		ft_printf("g_signal [%i]\n", g_signal);
		if (!str)
			exit_handler(ms, 1);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] && str[ft_strlen(limiter)] == '\n')
			return (free(str));
		if (ft_putstr_fd(str, ms->exec->pipe_fd[(i + 1) % 2][1]) < 0)
		{
			free(str);
			exit_handler(ms, 1);
		}
		free(str);
	}
}

void	solo_exec_here_doc(t_ms *ms, char *limiter)
{
	char	*str;

	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
			exit_handler(ms, 1);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] && str[ft_strlen(limiter)] == '\n')
		{
			free(str);
			return ;
		}
		free(str);
	}
}

void	init_here_doc(t_ms *ms, t_cmd *cmd, int i)
{
	size_t	index;

	index = 0;
	while (cmd->files_size > index)
	{
		if (cmd->files[index]->type == IN && cmd->files[index]->is_lim)
			exec_here_doc(ms, cmd->files[index]->name, i);
		index++;
	}
}