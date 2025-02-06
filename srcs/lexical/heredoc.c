#include "minishell.h"

void	here_doc(t_ms *ms, char *limiter)
{
	char	*str;
	int		fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit_handler(ms, 1);
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
			exit_handler(ms, 1);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			free(str);
			close (fd);
			fd = open(".heredoc.tmp", O_RDONLY);
			if (fd < 0)
				exit_handler(ms, 1);
			unlink(".heredoc.tmp");
			ms->here_doc_fd = fd;
			return ;
		}
		if (ft_putstr_fd(str, fd) < 0)
		{
			free(str);
			exit_handler(ms, 1);
		}
		free(str);
	}
}
