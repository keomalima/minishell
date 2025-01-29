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
	exit(WEXITSTATUS(status));
}

void	open_file(t_cmd *cmd, t_ms *ms, int i)
{
	if (cmd->infile)
	{
		ms->exec.pipe_fd[(i + 1) % 2][0] = open(cmd->infile, O_RDONLY);
		if (ms->exec.pipe_fd[(i + 1) % 2][0] < 0)
		{
			if (access(cmd->infile, R_OK) < 0
				&& access(cmd->infile, F_OK) == 0)
				ft_printf("%s: %s \n", strerror(errno), cmd->infile);
			else
				ft_printf("%s: %s \n", strerror(errno), cmd->infile);
			exit_handler(ms, -1);
		}
	}
	else if (cmd->outfile)
	{
		if (cmd->redir == OUT_TRUNC)
		{
			ms->exec.pipe_fd[i % 2][1] = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			ms->exec.pipe_fd[i % 2][1] = open(cmd->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (ms->exec.pipe_fd[i % 2][1] < 0)
		{
			ft_printf("%s: %s \n", strerror(errno), cmd->outfile);
			exit_handler(ms, -1);
		}
	}
}

void	print_fds(t_ms *ms, int it)
{
	int i = 0;

	while (2 > i)
	{
		printf("Iteration [%i]\n", it);
		if (ms->exec.pipe_fd[i][0] > 0)
			printf("FD 1 read open [%i]\n", ms->exec.pipe_fd[i][0]);
		if (ms->exec.pipe_fd[i][1] > 0)
			printf("FD 1 write open [%i]\n", ms->exec.pipe_fd[i][1]);
		i++;
	}
}

void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	//print_fds(ms, i);
	if (cmd->infile || cmd->outfile)
		open_file(cmd, ms, i);
	ms->exec.cmd = parse_arg(cmd, ms);
	// if (dup2(ms->exec.pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
	// 	exit_handler(ms, 1);
	// if (dup2(ms->exec.pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
	// 	exit_handler(ms, 1);
	// close_all_fds(ms);
	// if (execve(ms->exec.cmd[0], ms->exec.cmd, NULL) == -1)
	// {
	// 	if (dup2(2, STDOUT_FILENO) < 0)
	// 		exit_handler(ms, 1);
	// 	ft_printf("%s: %s\n", strerror(errno), ms->exec.cmd[0]);
	// 	exit_handler(ms, 126);
	// }
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
		printf("CMD count [%i]\n", ms->exec.cmd_count);
		//printf("CMD [%s] on iteration [%i]\n", current->cmd[i], i);
		// if (ms->exec.cmd_count > i - 1 > i)
		// 	if (pipe(ms->exec.pipe_fd[i % 2]) < 0)
		// 		exit_handler(ms, 1);
		// switch_io_n_execve(current, ms, i);
		// ms->exec.child_pids[i] = fork();
		// if (ms->exec.child_pids[i] < 0)
		// 	exit_handler(ms, -1);
		// if (ms->exec.child_pids[i] == 0)
		// 	switch_io_n_execve(current, ms, i);
		// close_fd(ms, &ms->exec.pipe_fd[i % 2][1]);
		// close_fd(ms, &ms->exec.pipe_fd[(i + 1) % 2][0]);
		current = current->next;
		i++;
	}
	wait_children_exit(ms);
}
