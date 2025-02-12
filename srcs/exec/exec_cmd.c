#include "minishell.h"

static void	open_outfile(t_cmd *cmd, t_ms *ms, int i)
{
	size_t	index;

	index = 0;
	while (cmd->outfile_size > index)
	{
		if (ms->exec->pipe_fd[i % 2][1] >= 0)
			close_fd(ms, &ms->exec->pipe_fd[i % 2][1]);
		if (cmd->outfile[index]->type == OUT_TRUNC)
			ms->exec->pipe_fd[i % 2][1] = open(cmd->outfile[index]->name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			ms->exec->pipe_fd[i % 2][1] = open(cmd->outfile[index]->name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ms->exec->pipe_fd[i % 2][1] < 0)
		{
			ft_printf("%s: %s \n", strerror(errno), cmd->outfile[index]->name);
			exit_handler(ms, -1);
		}
		index++;
	}
}

static void	open_infile(t_cmd *cmd, t_ms *ms, int i)
{
	size_t	index;

	index = 0;
	while (cmd->infile_size > index)
	{
		if (ms->exec->pipe_fd[(i % 2) % 2][0] >= 0)
			close_fd(ms, &ms->exec->pipe_fd[(i % 2) % 2][0]);
		if (cmd->infile[i]->is_lim)
			exec_here_doc(ms, cmd->infile[i]->name, i);
		else
			ms->exec->pipe_fd[(i + 1) % 2][0] = open(cmd->infile[index]->name,
					O_RDONLY);
		if (ms->exec->pipe_fd[(i + 1) % 2][0] < 0)
		{
			if (access(cmd->infile[index]->name, R_OK) < 0
				&& access(cmd->infile[index]->name, F_OK) == 0)
				ft_printf("%s: %s \n", strerror(errno),
					cmd->infile[index]->name);
			else
				ft_printf("%s: %s \n", strerror(errno),
					cmd->infile[index]->name);
			exit_handler(ms, -1);
		}
		index++;
	}
}

static void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	if (cmd->infile_size)
		open_infile(cmd, ms, i);
	if (cmd->outfile_size)
		open_outfile(cmd, ms, i);
	if (cmd->cmd[0])
		ms->exec->cmd = parse_arg(cmd, ms);
	if (dup2(ms->exec->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0
		&& ms->exec->pipe_fd[(i + 1) % 2][0] > 0)
		exit_handler(ms, 1);
	if (cmd->redir != UNDEFINED
		&& dup2(ms->exec->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
	close_all_fds(ms);
	if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "cd") == 0)
		cd_command(ms, cmd);
	else if (cmd->cmd[0] && ft_strcmp(cmd->cmd[0], "export") == 0)
		export_command(ms, cmd);
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