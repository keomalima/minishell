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

static void	clean_t_cmd(t_ms *ms)
{
	t_cmd	*tmp;
	int		i;

	if (ms->cmd)
	{
		tmp = ms->cmd;
		while (tmp)
		{
			i = 0;
			while (tmp->outfile[i])
				free(tmp->outfile[i++]);
			free(tmp->outfile);
			tmp->outfile = NULL;
			i = 0;
			while (tmp->infile[i])
				free(tmp->infile[i++]);
			free(tmp->infile);
			tmp->infile = NULL;
			if (ms->cmd->cmd)
				free(ms->cmd->cmd);
			ms->cmd->cmd = NULL;
			ms->cmd = ms->cmd->next;
			free(tmp);
			tmp = NULL;
			tmp = ms->cmd;
		}
	}
}

void	clean_ms(t_ms *ms, int exit_code)
{
	clean_t_token(ms);
	clean_t_cmd(ms);
	clean_t_exec(ms->exec, ms);
	ms->exit_status = exit_code;
}

void	exit_handler(t_ms *ms, int exit_code)
{
	clean_t_token(ms);
	clean_t_cmd(ms);
	clean_t_exec(ms->exec, ms);
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
	exit(exit_code);
}