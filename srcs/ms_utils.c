#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (0);
	else
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

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
		lst->content = NULL;
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
			free ((*cmd)->outfile);
			(*cmd)->outfile = NULL;
			free ((*cmd)->infile);
			(*cmd)->infile = NULL;
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
	ms->exit_status = exit_code;
	printf(RED"--> exit code = %d\n"RESET, ms->exit_status);
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