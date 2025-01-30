#include "minishell.h"

void	wait_children_exit(t_ms *ms)
{
	int	i;
	int	status;

	i = 0;
	while (ms->exec.cmd_count > i)
	{
		if (waitpid(ms->exec.child_pids[i], &status, 0) < 0)
			exit_handler(ms, 1);
		i++;
	}
	free(ms->exec.child_pids);
	ms->exec.child_pids = NULL;
	exit_handler(ms, WEXITSTATUS(status));
}

void	open_file(t_cmd *cmd, t_ms *ms, int i)
{
	if (cmd->infile_size)
	{
		ms->exec.pipe_fd[(i + 1) % 2][0] = open(cmd->infile[cmd->infile_size - 1], O_RDONLY);
		if (ms->exec.pipe_fd[(i + 1) % 2][0] < 0)
		{
			if (access(cmd->infile[cmd->infile_size - 1], R_OK) < 0
				&& access(cmd->infile[cmd->infile_size - 1], F_OK) == 0)
				ft_printf("%s: %s \n", strerror(errno), cmd->infile[cmd->infile_size - 1]);
			else
				ft_printf("%s: %s \n", strerror(errno), cmd->infile[cmd->infile_size - 1]);
			exit_handler(ms, -1);
		}
	}
	else if (cmd->outfile_size)
	{
		if (cmd->redir == OUT_TRUNC)
		{
			ms->exec.pipe_fd[i % 2][1] = open(cmd->outfile[cmd->outfile_size - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			ms->exec.pipe_fd[i % 2][1] = open(cmd->outfile[cmd->outfile_size - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (ms->exec.pipe_fd[i % 2][1] < 0)
		{
			ft_printf("%s: %s \n", strerror(errno), cmd->outfile[cmd->outfile_size - 1]);
			exit_handler(ms, -1);
		}
	}
}

void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	if (cmd->infile_size || cmd->outfile_size)
		open_file(cmd, ms, i);
	ms->exec.cmd = parse_arg(cmd, ms);
	if (dup2(ms->exec.pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0
		&& ms->exec.pipe_fd[(i + 1) % 2][0] > 0)
		exit_handler(ms, 1);
	if (dup2(ms->exec.pipe_fd[i % 2][1], STDOUT_FILENO) < 0
		&& cmd->redir != UNDEFINED)
		exit_handler(ms, 1);
	close_all_fds(ms);
	if (execve(ms->exec.cmd[0], ms->exec.cmd, NULL) == -1)
	{
		if (dup2(2, STDOUT_FILENO) < 0)
			exit_handler(ms, 1);
		ft_printf("%s: %s\n", strerror(errno), ms->exec.cmd[0]);
		exit_handler(ms, 126);
	}
}

void	exec_cmd(t_ms *ms)
{
	int		i;
	t_cmd	*current;

	current = ms->cmd;
	initialize_variables(ms);
	ms->exec.cmd_count = ft_cmd_count(ms);
	ms->exec.child_pids = malloc (ms->exec.cmd_count * sizeof(pid_t));
	if (!ms->exec.child_pids)
		exit_handler(ms, 12);
	i = 0;
	while (current)
	{
		if (ms->exec.cmd_count - 1 > i)
			if (pipe(ms->exec.pipe_fd[i % 2]) < 0)
				exit_handler(ms, 1);
		ms->exec.child_pids[i] = fork();
		if (ms->exec.child_pids[i] < 0)
			exit_handler(ms, -1);
		if (ms->exec.child_pids[i] == 0)
			switch_io_n_execve(current, ms, i);
		close_fd(ms, &ms->exec.pipe_fd[i % 2][1]);
		close_fd(ms, &ms->exec.pipe_fd[(i + 1) % 2][0]);
		i++;
		current = current->next;
	}
	wait_children_exit(ms);
}
