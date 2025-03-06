#include "minishell.h"

void	exec_here_doc(t_ms *ms, char *limiter, int i)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	if (pipe(ms->exec->pipe_fd[(i + 1) % 2]) < 0)
	exit_handler(ms, 1);
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
		{
			close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
			close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][1]);
			exit_handler(ms, 1);
		}
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] && str[ft_strlen(limiter)] == '\n')
		{
			free(str);
			close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][1]);
			return ;
		}
		if (ft_putstr_fd(str, ms->exec->pipe_fd[(i + 1) % 2][1]) < 0)
		{
			free(str);
			close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
			close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][1]);
			exit_handler(ms, 1);
		}
		free(str);
	}
}

void	solo_exec_here_doc(t_ms *ms, char *limiter)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
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