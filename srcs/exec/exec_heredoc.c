/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:52:10 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 15:18:28 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_str_pipe(char **str, t_ms *ms, char *limiter)
{
	size_t	len;

	len = ft_strlen(limiter);
	if (len <= 1 || (limiter[0] != limiter[len - 1])
		|| (limiter[0] != '"' && limiter[0] != '\''))
	{
		if (*str && *str[0] != 0)
			*str = ft_translate(*str, ms, 1);
	}
	if (ft_putstr_fd(*str, ms->exec->pipe_hd[1]) < 0
		|| ft_putstr_fd("\n", ms->exec->pipe_hd[1]) < 0)
	{
		close_fd(ms, &ms->exec->pipe_hd[0]);
		close_fd(ms, &ms->exec->pipe_hd[1]);
		free(*str);
		*str = NULL;
		exit_handler(ms, 1);
	}
}

static int	exec_here_doc(t_ms *ms, char *limiter, char *str)
{
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (sigquit_handler(ms));
		if (g_signal != 0)
		{
			if (str)
				free(str);
			close_fd(ms, &ms->exec->pipe_hd[0]);
			close_fd(ms, &ms->exec->pipe_hd[1]);
			return (1);
		}
		if (!ft_strcmp(limiter, str))
		{
			free(str);
			break ;
		}
		add_str_pipe(&str, ms, limiter);
		free(str);
	}
	return (0);
}

int	init_here_doc(t_ms *ms, char *limiter)
{
	char	*str;
	int		hd;

	rl_event_hook = check_interupt;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_here_doc);
	str = NULL;
	if (pipe(ms->exec->pipe_hd) < 0)
		exit_handler(ms, 1);
	hd = exec_here_doc(ms, limiter, str);
	if (hd == 1)
		return (1);
	else if (hd == 2)
		return (2);
	handle_hd_fds(ms);
	return (0);
}

int	solo_exec_here_doc(t_ms *ms, char *limiter)
{
	char	*str;

	rl_event_hook = check_interupt;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_here_doc);
	while (1)
	{
		str = readline("> ");
		if (g_signal != 0)
		{
			if (str)
				free(str);
			return (1);
		}
		if (!str)
			return (sigquit_handler(ms));
		if (!ft_strcmp(limiter, str))
		{
			free(str);
			return (1);
		}
		free(str);
	}
}
