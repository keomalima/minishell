#include "minishell.h"

static void	clean_t_exec(t_exec *args, t_ms *ms)
{
	if (args)
	{
		close_all_fds(ms);
		if (args->child_pids)
			free(args->child_pids);
		free(args);
		args = NULL;
	}
}

static void	clean_t_token(t_ms *ms)
{
	t_token	*tmp;

	if (ms->token)
	{
		while (ms->token)
		{
			if (ms->token->content)
			{
				free(ms->token->content);
				ms->token->content = NULL;
			}
			tmp = ms->token;
			ms->token = ms->token->next;
			free(tmp);
			tmp = NULL;
		}
	}
}

void	clean_t_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	if (cmd)
	{
		tmp = cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->files && tmp->files[i])
				free(tmp->files[i++]);
			free(tmp->files);
			tmp->files = NULL;
			if (tmp->cmd)
				free_split(tmp->cmd);
			tmp->cmd = NULL;
			cmd = cmd->next;
			free(tmp);
			tmp = NULL;
			tmp = cmd;
		}
	}
}

void	clean_ms(t_ms *ms, int exit_code)
{
	clean_t_token(ms);
	clean_t_cmd(ms->cmd);
	clean_t_exec(ms->exec, ms);
	if (exit_code >= 0)
		ms->exit_status = exit_code;
}

void	exit_handler(t_ms *ms, int exit_code)
{
	clean_t_token(ms);
	clean_t_cmd(ms->cmd);
	clean_t_exec(ms->exec, ms);
	if (ms->input_main)
		free(ms->input_main);
	if (ms->env)
		free_split(ms->env);
	ms->exit_status = exit_code;
	if (exit_code == -1)
	{
		exit_code = 1;
		errno = 0;
	}
	if (exit_code == 127 || exit_code == 126)
		errno = 0;
	if (exit_code == 12)
		errno = ENOMEM;
	if (errno && exit_code != 0)
		perror("Error");
	close_fd (ms, &ms->saved_in);
	close_fd (ms, &ms->saved_out);
	exit(exit_code);
}
