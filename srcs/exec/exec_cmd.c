#include "minishell.h"

static void	handle_signals(t_ms *ms, int status, int sigint_handled)
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

void	wait_children(t_ms *ms)
{
	int	i;
	int	status;
	int	sigint_handled;

	i = 0;
	sigint_handled = 0;
	while (i < ms->exec->cmd_count)
	{
		if (waitpid(ms->exec->child_pids[i], &status, 0) < 0)
			exit_handler(ms, 1);
		if (WIFSIGNALED(status))
		{
			handle_signals(ms, status, sigint_handled);
			sigint_handled = 1;
		}
		else
			ms->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	file_handler(cmd, ms, i);
	if (cmd->cmd[0])
		ms->exec->cmd = parse_arg(cmd, ms);
	if (ms->exec->pipe_fd[(i + 1) % 2][0] > 0
		&& dup2(ms->exec->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
		exit_handler(ms, 1);
	if (cmd->redir != UNDEFINED
		&& dup2(ms->exec->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
	close_all_fds(ms);
	exec_builtin(ms, cmd);
	if (!cmd->cmd[0])
		exit_handler(ms, 0);
	if (execve(ms->exec->cmd[0], ms->exec->cmd, ms->env) == -1)
	{
		ft_print_error(strerror(errno), ms->exec->cmd[0], "\n");
		exit_handler(ms, 126);
	}
}

static void	exec_cmd(t_ms *ms, t_cmd *current)
{
	int		i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (current)
	{
		if (ms->exec->cmd_count - 1 > i)
			if (pipe(ms->exec->pipe_fd[i % 2]) < 0)
				exit_handler(ms, 1);
		init_here_doc(ms, current, i);
		if (g_signal > 0)
			return ;
		ms->exec->child_pids[i] = fork();
		if (ms->exec->child_pids[i] < 0)
			exit_handler(ms, -1);
		if (ms->exec->child_pids[i] == 0)
			switch_io_n_execve(current, ms, i);
		close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
		close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][1]);
		close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
		i++;
		current = current->next;
	}
	wait_children(ms);
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

void	exec_init(t_ms *ms)
{
	t_cmd	*current;

	if (ms->cmd)
	{
		ms->exec = ft_calloc(sizeof(t_exec), 1);
		if (!ms->exec)
			exit_handler(ms, 12);
		initialize_variables(ms);
		ms->exec->cmd_count = ft_cmd_count(ms);
		ms->exec->child_pids = ft_calloc (ms->exec->cmd_count * sizeof(pid_t), 1);
		if (!ms->exec->child_pids)
			exit_handler(ms, 12);
		current = ms->cmd;
		if (current->cmd[0] && is_builtin_solo_cmd(ms, current->cmd[0]))
			return (handle_solo_builtins_exec(ms, current));
		exec_cmd(ms, current);
	}
}
