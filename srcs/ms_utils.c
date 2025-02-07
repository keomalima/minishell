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

char	*ft_getenv(t_ms *ms, char *str)
{
	int	i;

	if (!ms || !ms->env)
		return (NULL);
	i = 0;
	while (ms->env[i])
	{
		if (ft_strncmp(ms->env[i], str, ft_strlen(str)) == 0 && ms->env[i][ft_strlen(str)] == '=')
			return (&ms->env[i][ft_strlen(str) + 1]);
		i++;
	}
}

static void	ft_lstdelone_token(t_token *lst)
{
	if (lst)
	{
		if (lst->content)
		{
			free(lst->content);
			lst->content = NULL;
		}
		free(lst);
		lst = NULL;
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

void	clean_ms(t_ms *ms, int exit_code)
{
	ms->exit_status = exit_code;
	ft_lstclear_token(&ms->token);
	ft_lstclear_cmd(&ms->cmd);
	exec_exit_handler(ms->exec, ms);
	// if (ms->mod_env == 1)
	// 	free_split(ms->env);
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
size_t	ft_strlcpy_ms(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (dst && src && size > 0)
	{
		i = 0;
		while (size - 1 > i && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen_ms(src));
}

size_t	ft_strlen_ms(const char *s)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
