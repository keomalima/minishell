#include "minishell.h"

static void	add_str_pipe(char **str, t_ms *ms, int i, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	if (len <= 1 || (limiter[0] != limiter[len - 1])
		|| (limiter[0] != '"' && limiter[0] != '\''))
		*str = ft_translate_heredoc(*str, ms);
	if (ft_putstr_fd(*str, ms->exec->pipe_fd[(i + 1) % 2][1]) < 0 ||
		ft_putstr_fd("\n", ms->exec->pipe_fd[(i + 1) % 2][1]) < 0)
	{
		free(*str);
		exit_handler(ms, 1);
	}
}

static void	exec_here_doc(t_ms *ms, char *limiter, int i)
{
	char	*str;

	//rl_event_hook = check_interupt;
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
		if (!str)
			return (sigquit_handler());
		if (!ft_strcmp_here_doc(limiter, str))
			return (free(str));
		add_str_pipe(&str, ms, i, limiter);
		free(str);
	}
}

int	solo_exec_here_doc(t_ms *ms, char *limiter)
{
	char	*str;

	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
		{
			ms->exit_status = 1;
			return (1);
		}
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] && str[ft_strlen(limiter)] == '\n')
		{
			free(str);
			return (0);
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
		if (g_signal != 0)
			return ;
		if (cmd->files[index]->type == IN && cmd->files[index]->is_lim)
			exec_here_doc(ms, cmd->files[index]->name, i);
		index++;
	}
}
