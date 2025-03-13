#include "minishell.h"

int	ft_strcmp_here_doc(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;

	if (s1[0] == '"' || s1[0] == '\'')
		s1++;
	len = ft_strlen(s1);
	if (len > 0 && (s1[len - 1] == '"' || s1[len - 1] == '\''))
		len--;
	i = 0;
	while (i < len && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == len && !s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_interupt(void)
{
	return (0);
}

void	sigint_here_doc(int sig)
{
	g_signal = sig;
	rl_done = 1;
}

int	sigquit_handler(t_ms *ms)
{
	if (ms->exec->pipe_hd[0] != -1)
		close_fd(ms, &ms->exec->pipe_hd[0]);
	if (ms->exec->pipe_hd[1] != -1)
		close_fd(ms, &ms->exec->pipe_hd[1]);
	ft_printf("minishell: warning: here-document delimited by"
		"end-of-file (wanted `EOF')\n");
	ms->exec->here_doc_quit = 1;
	return (2);
}

void	handle_hd_fds(t_ms *ms)
{
	if (ms->exec->fd_in != -1)
		close_fd(ms, &ms->exec->fd_in);
	close_fd(ms, &ms->exec->pipe_hd[1]);
	ms->exec->fd_in = dup(ms->exec->pipe_hd[0]);
	close_fd(ms, &ms->exec->pipe_hd[0]);
	if (ms->exec->fd_in < 0)
		exit_handler(ms, 1);
}
