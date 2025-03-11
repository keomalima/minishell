#include "minishell.h"

void	handle_signals(t_ms *ms, int status, int sigint_handled)
{
	if (WTERMSIG(status) == SIGINT && !sigint_handled)
	{
		ft_printf("\n");
		ms->exit_status = 130;
	}
	else if (WTERMSIG(status) == SIGQUIT && !sigint_handled)
	{
		ft_print_error("Quit (core dumped)\n", NULL, NULL);
		ms->exit_status = 131;
	}
}

void	handle_solo_builtins_exec(t_ms *ms, t_cmd *current)
{
	if (!solo_file_handler(ms->cmd, ms))
		return ;
	exec_builtin(ms, current);
	if (dup2(ms->saved_in, STDIN_FILENO) < 0)
		exit_handler(ms, 1);
	if (dup2(ms->saved_out, STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
}

void	close_exec_fds(t_ms *ms, int i)
{
	if (ms->exec->pipe_fd[i % 2][1] != -1)
		close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
	if (ms->exec->pipe_fd[(i + 1) % 2][0] != -1)
		close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
	if (ms->exec->fd_in != -1)
		close_fd(ms, &ms->exec->fd_in);
	if (ms->exec->fd_out != -1)
		close_fd(ms, &ms->exec->fd_out);
}
