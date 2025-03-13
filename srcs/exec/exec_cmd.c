#include "minishell.h"

void	wait_children(t_ms *ms, int i)
{
	int	j;
	int	status;
	int	sigint_handled;

	sigint_handled = 0;
	j = 0;
	while (i > j)
	{
		if (waitpid(ms->exec->child_pids[j], &status, 0) < 0)
			exit_handler(ms, 1);
		j++;
	}
	if (WIFSIGNALED(status))
	{
		handle_signals(ms, status, sigint_handled);
		sigint_handled = 1;
	}
	else
		ms->exit_status = WEXITSTATUS(status);
}

static void	handle_dup(t_cmd *cmd, t_ms *ms, int i)
{
	if (ms->exec->fd_in != -1)
	{
		close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
		ms->exec->pipe_fd[(i + 1) % 2][0] = dup(ms->exec->fd_in);
		if (ms->exec->pipe_fd[(i + 1) % 2][0] < 0)
			exit_handler(ms, 1);
	}
	if (ms->exec->pipe_fd[(i + 1) % 2][0] > 0
		&& ms->exec->pipe_fd[(i + 1) % 2][0] != STDIN_FILENO)
	{
		if (dup2(ms->exec->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
			exit_handler(ms, 1);
	}
	if (ms->exec->fd_out != -1)
	{
		close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
		ms->exec->pipe_fd[i % 2][1] = dup(ms->exec->fd_out);
		if (ms->exec->pipe_fd[i % 2][1] < 0)
			exit_handler(ms, 1);
	}
	if (cmd->redir != UNDEFINED && ms->exec->pipe_fd[i % 2][1] > 0
		&& ms->exec->pipe_fd[i % 2][1] != STDOUT_FILENO)
	{
		if (dup2(ms->exec->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
			exit_handler(ms, 1);
	}
	close_all_fds(ms);
}

void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ms->exec->in_file_err || ms->exec->out_file_err)
	{
		if (ms->exec->here_doc_quit)
			exit_handler(ms, 0);
		exit_handler(ms, -1);
	}
	if (cmd->cmd[0])
		ms->exec->cmd = parse_arg(cmd, ms);
	handle_dup(cmd, ms, i);
	exec_builtin(ms, cmd);
	if (!cmd->cmd[0])
		exit_handler(ms, 0);
	if (execve(ms->exec->cmd[0], ms->exec->cmd, ms->env) == -1)
	{
		ft_print_error(strerror(errno), ms->exec->cmd[0], "\n");
		exit_handler(ms, 126);
	}
}

static void	exec_cmd(t_ms *ms, t_cmd *current, int i)
{
	while (current)
	{
		if (ms->exec->cmd_count - 1 > i)
			if (pipe(ms->exec->pipe_fd[i % 2]) < 0)
				exit_handler(ms, 1);
		file_handler(ms, current, i);
		if (g_signal > 0)
			return ;
		ms->exec->child_pids[i] = fork();
		if (ms->exec->child_pids[i] < 0)
			exit_handler(ms, -1);
		if (ms->exec->child_pids[i] == 0)
			switch_io_n_execve(current, ms, i);
		close_exec_fds(ms, i);
		ms->exec->here_doc_quit = 0;
		i++;
		current = current->next;
	}
	wait_children(ms, i);
}

void	exec_init(t_ms *ms)
{
	t_cmd	*current;
	int		i;

	i = 0;
	if (ms->cmd)
	{
		ms->exec = ft_calloc(sizeof(t_exec), 1);
		if (!ms->exec)
			exit_handler(ms, 12);
		initialize_variables(ms);
		ms->exec->cmd_count = ft_cmd_count(ms);
		ms->exec->child_pids = ft_calloc(ms->exec->cmd_count, sizeof(pid_t));
		if (!ms->exec->child_pids)
			exit_handler(ms, 12);
		current = ms->cmd;
		if (current->cmd[0] && is_builtin_solo_cmd(ms, current->cmd[0]))
			return (handle_solo_builtins_exec(ms, current));
		signal(SIGINT, SIG_IGN);
		exec_cmd(ms, current, i);
	}
}
