#include "minishell.h"

void	exec_exit_handler(t_exec *args, t_ms *ms)
{
	if (args)
	{
		close_all_fds(ms);
		if (args->cmd)
	 		free_split(args->cmd);
		if (args->child_pids)
			free(args->child_pids);
		free(args);
	}
}

static void	ft_lstdelone_token(t_token *lst)
{
	if (lst)
	{
		free(lst->content);
		free(lst);
	}
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone_token(tmp);
		}
	}
}

void	ft_lstclear_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (cmd)
	{
		while (*cmd)
		{
			tmp = *cmd;
			*cmd = (*cmd)->next;
			if (tmp)
			{
				free(tmp->cmd);
				free(tmp);
			}
		}
	}
}

void	exit_handler(t_ms *ms, int exit_code)
{
	ft_lstclear_token(&ms->token);
	ft_lstclear_cmd(&ms->cmd);
	exec_exit_handler(ms->exec, ms);
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