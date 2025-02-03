#include "minishell.h"

int	ft_cmd_count(t_ms *ms)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = ms->cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

void	close_fd(t_ms *ms, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) < 0)
			exit_handler(ms, 1);
		*fd = -1;
	}
}

void	close_all_fds(t_ms *ms)
{
	int	i;

	i = 0;
	while (2 > i)
	{
		close_fd(ms, &ms->exec->pipe_fd[i][0]);
		close_fd(ms, &ms->exec->pipe_fd[i][1]);
		i++;
	}
}

void	initialize_variables(t_ms *ms)
{
	ms->exec->here_doc = 0;
	ms->exec->cmd_count = 0;
	ms->exec->env = NULL;
	ms->exec->cmd = NULL;
	ms->exec->child_pids = NULL;
	ms->exec->pipe_fd[0][0] = -1;
	ms->exec->pipe_fd[0][1] = -1;
	ms->exec->pipe_fd[1][0] = -1;
	ms->exec->pipe_fd[1][1] = -1;
}