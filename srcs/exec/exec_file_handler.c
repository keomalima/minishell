#include "minishell.h"

static int	open_outfile(t_ms *ms, char *name, t_redir type)
{
	if (ms->exec->fd_out != -1)
		close_fd(ms, &ms->exec->fd_out);
	if (type == OUT_TRUNC)
		ms->exec->fd_out = open(name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		ms->exec->fd_out = open(name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ms->exec->fd_out < 0)
	{
		ft_print_error("minishell: ", name, ": ");
		ft_print_error(strerror(errno), " \n", NULL);
		ms->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	open_infile(t_ms *ms, char *name, int is_lim)
{
	if (ms->exec->fd_in != -1)
		close_fd(ms, &ms->exec->fd_in);
	if (is_lim)
	{
		if (init_here_doc(ms, name))
			return (1);
	}
	else
		ms->exec->fd_in = open(name, O_RDONLY);
	if (ms->exec->fd_in < 0)
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
		ms->exit_status = 1;
		return (1);
	}
	return (0);
}

int	file_handler(t_ms *ms, t_cmd *cmd)
{
	size_t	index;

	index = 0;
	while (cmd->files_size > index)
	{
		if (g_signal != 0)
			return (1);
		if (cmd->files[index]->type == IN)
		{
			if (open_infile(ms, cmd->files[index]->name,
					cmd->files[index]->is_lim))
				return (1);
		}
		else
		{
			if (open_outfile(ms, cmd->files[index]->name,
					cmd->files[index]->type))
				return (1);
		}
		index++;
	}
	return (0);
}
