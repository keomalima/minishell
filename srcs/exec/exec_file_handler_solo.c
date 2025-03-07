#include "minishell.h"

static void	solo_open_outfile(t_ms *ms, char *name, t_redir type)
{
	int	fd;

	if (type == OUT_TRUNC)
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_print_error("minishell: ", name, ": ");
		ft_print_error(strerror(errno), " \n", NULL);
		exit_handler(ms, -1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		exit_handler(ms, 1);
	close(fd);
}

static void	solo_open_infile(t_ms *ms, char *name, int is_lim)
{
	int	fd;

	if (is_lim)
	{
		solo_exec_here_doc(ms, name);
		return ;
	}
	else
		fd = open(name, O_RDONLY);
	if (fd < 0)
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
	if (dup2(fd, STDIN_FILENO) < 0)
		exit_handler(ms, 1);
	close(fd);
}


void	solo_file_handler(t_cmd *cmd, t_ms *ms)
{
	size_t	index;

	index = 0;
	while (cmd->files_size > index)
	{
		if (cmd->files[index]->type == IN)
			solo_open_infile(ms, cmd->files[index]->name, cmd->files[index]->is_lim);
		else
			solo_open_outfile(ms, cmd->files[index]->name, cmd->files[index]->type);
		index++;
	}
}
