#include "minishell.h"

static void	open_outfile(t_ms *ms, int i, char *name, t_redir type)
{
	if (ms->exec->pipe_fd[i % 2][1] >= 0)
		close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
	if (type == OUT_TRUNC)
		ms->exec->pipe_fd[i % 2][1] = open(name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		ms->exec->pipe_fd[i % 2][1] = open(name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ms->exec->pipe_fd[i % 2][1] < 0)
	{
		ft_printf("%s: %s \n", strerror(errno), name);
		exit_handler(ms, -1);
	}
}

static void	open_infile(t_ms *ms, int i, char *name, int is_lim)
{
	if (ms->exec->pipe_fd[(i % 2) % 2][0] >= 0)
		close_fd(ms, &ms->exec->pipe_fd[(i % 2) % 2][0]);
	if (is_lim)
		exec_here_doc(ms, name, i);
	else
		ms->exec->pipe_fd[(i + 1) % 2][0] = open(name, O_RDONLY);
	if (ms->exec->pipe_fd[(i + 1) % 2][0] < 0)
	{
		if (access(name, R_OK) < 0 && access(name, F_OK) == 0)
			ft_printf("%s: %s \n", strerror(errno), name);
		else
			ft_printf("%s: %s \n", strerror(errno), name);
		exit_handler(ms, -1);
	}
}

static void	file_handler(t_cmd *cmd, t_ms *ms, int i)
{
	size_t	index;

	index = 0;
	while (cmd->files_size > index)
	{
		if (cmd->files[index]->type == IN)
			open_infile(ms, i, cmd->files[index]->name,
				cmd->files[index]->is_lim);
		else
			open_outfile(ms, i, cmd->files[index]->name,
				cmd->files[index]->type);
		index++;
	}
}

static void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	if (cmd->files_size)
		file_handler(cmd, ms, i);
	if (cmd->cmd[0])
		ms->exec->cmd = parse_arg(cmd, ms);
	if (dup2(ms->exec->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0
		&& ms->exec->pipe_fd[(i + 1) % 2][0] > 0)
		exit_handler(ms, 1);
	if (cmd->redir != UNDEFINED
		&& dup2(ms->exec->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
	close_all_fds(ms);
	exec_builtin(ms, cmd);
	if (execve(ms->exec->cmd[0], ms->exec->cmd, NULL) == -1)
	{
		if (dup2(2, STDOUT_FILENO) < 0)
			exit_handler(ms, 1);
		ft_printf("%s: %s\n", strerror(errno), ms->exec->cmd[0]);
		exit_handler(ms, 126);
	}
}

static void	exec_cmd(t_ms *ms)
{
	int		i;
	int		status;
	t_cmd	*current;

	current = ms->cmd;
	i = 0;
	while (current)
	{
		if (ms->exec->cmd_count - 1 > i)
			if (pipe(ms->exec->pipe_fd[i % 2]) < 0)
				exit_handler(ms, 1);
		ms->exec->child_pids[i] = fork();
		if (ms->exec->child_pids[i] < 0)
			exit_handler(ms, -1);
		if (ms->exec->child_pids[i] == 0)
			switch_io_n_execve(current, ms, i);
		close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
		close_fd(ms, &ms->exec->pipe_fd[(i + 1) % 2][0]);
		if (waitpid(ms->exec->child_pids[i], &status, 0) < 0)
			exit_handler(ms, 1);
		ms->exit_status = WEXITSTATUS(status);
		i++;
		current = current->next;
	}
}

void	exec_init(t_ms *ms)
{
	ms->exec = malloc(sizeof(t_exec));
	if (!ms->exec)
		exit_handler(ms, 12);
	initialize_variables(ms);
	ms->exec->cmd_count = ft_cmd_count(ms);
	ms->exec->child_pids = malloc (ms->exec->cmd_count * sizeof(pid_t));
	if (!ms->exec->child_pids)
		exit_handler(ms, 12);
	exec_cmd(ms);
}