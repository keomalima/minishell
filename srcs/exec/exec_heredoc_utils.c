/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:52:15 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 15:01:50 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_interupt(void)
{
	return (0);
}

void	sigint_here_doc(int sig)
{
	g_signal = sig;
	rl_done = 1;
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

int	sigquit_handler(t_ms *ms)
{
	ft_printf("minishell: warning: here-document delimited by"
		"end-of-file (wanted `EOF')\n");
	ms->exec->here_doc_quit = 1;
	handle_hd_fds(ms);
	return (2);
}
