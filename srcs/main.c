/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:54:16 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 15:50:42 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	initialize_ms(t_ms *ms)
{
	ms->token = NULL;
	ms->cmd = NULL;
	ms->exec = NULL;
	ms->lex_err = NULL;
	ms->input_main = NULL;
}

static void	run_minishell(t_ms *ms)
{
	char	*rl;

	rl = ms->input_main;
	if (handle_key(rl))
		return (clean_ms(ms, 0));
	create_tokens(rl, ms);
	if (lexical_analysis(ms))
		return (clean_ms(ms, 2));
	parse_cmd(ms);
	exec_init(ms);
	clean_ms(ms, -1);
}

static int	arg_check(t_ms *ms)
{
	if (ft_strlen(ms->input_main) > ARG_MAX)
	{
		ft_print_error("arg list too long \n", NULL, NULL);
		free(ms->input_main);
		return (1);
	}
	return (0);
}

static void	minishell(t_ms *ms)
{
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		initialize_ms(ms);
		ms->input_main = readline("minishell$ ");
		if (arg_check(ms))
			continue ;
		if (g_signal)
		{
			ms->exit_status = 130;
			g_signal = 0;
		}
		if (!ms->input_main)
		{
			printf("exit\n");
			exit_handler(ms, 0);
			break ;
		}
		add_history(ms->input_main);
		run_minishell(ms);
		free(ms->input_main);
		ms->input_main = NULL;
	}
}

int	main(int arc, char **arv, char **env)
{
	t_ms	ms;

	if (!isatty(STDOUT_FILENO) || !isatty(STDIN_FILENO))
	{
		ft_print_error("minishell: not a tty\n", NULL, NULL);
		return (-1);
	}
	(void)arc;
	(void)arv;
	ms.exit_status = 0;
	ms.env = ft_duplicate_env(env);
	ms.saved_in = dup(STDIN_FILENO);
	ms.saved_out = dup(STDOUT_FILENO);
	if (ms.saved_in < 0 || ms.saved_out < 0)
		exit_handler(&ms, 1);
	minishell(&ms);
	return (0);
}
