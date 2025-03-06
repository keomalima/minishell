#include "minishell.h"

void	here_doc_teste(t_ms *ms, char *limiter, int i)
{
	char	*str;

	if (pipe(ms->exec->pipe_fd[(i + 1) % 2]) < 0)
		exit_handler(ms, 1);
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
		if (ft_putstr_fd(str, ms->exec->pipe_fd[(i + 1) % 2][1]) < 0)
		{
			free(str);
			exit_handler(ms, 1);
		}
		free(str);
	}
}

void	switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i)
{
	if (ms->exec->pipe_fd[(i + 1) % 2][0] > 0
		&& dup2(ms->exec->pipe_fd[(i + 1) % 2][0], STDIN_FILENO) < 0)
		exit_handler(ms, 1);
	if (dup2(ms->exec->pipe_fd[i % 2][1], STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
	close_all_fds(ms);
	if (execve(ms->exec->cmd[0], ms->exec->cmd, ms->env) == -1)
		exit_handler(ms, 126);
}

int	ft_fork(t_ms *ms, t_cmd *current)
{
	int		i;

	i = 0;
	while (current)
	{
		if (ms->exec->cmd_count - 1 > i)
		{
			
		}
			if (pipe(ms->exec->pipe_fd[i % 2]) < 0)
				exit_handler(ms, 1);
		if (current->files[0]->is_lim)
			here_doc_teste(ms, current->files[0].name, i);
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