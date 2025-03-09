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
		ft_print_error("minishell: ", name, ": ");
		ft_print_error(strerror(errno), " \n", NULL);
		exit_handler(ms, -1);
	}
}

static void	open_infile(t_ms *ms, int i, char *name, int is_lim)
{
	if (ms->exec->pipe_fd[(i % 2) % 2][0] >= 0)
		close_fd(ms, &ms->exec->pipe_fd[(i % 2) % 2][0]);
	if (!is_lim)
		ms->exec->pipe_fd[(i + 1) % 2][0] = open(name, O_RDONLY);
	if (ms->exec->pipe_fd[(i + 1) % 2][0] < 0)
	{
		if (access(name, R_OK) < 0 && access(name, F_OK) == 0)
		{
			ft_print_error("minishell: ", name, ": ");
			ft_print_error(strerror(errno), " \n", NULL);
		}
		else
		{
			ft_print_error("minishell: ", name, ": ");
			ft_print_error(strerror(errno), " \n", NULL);
		}
		exit_handler(ms, -1);
	}
}

void	file_handler(t_cmd *cmd, t_ms *ms, int i)
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
