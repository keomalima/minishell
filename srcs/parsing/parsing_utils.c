#include "minishell.h"

size_t	is_opp_file(const char *s1)
{
	int			i;
	const char	*valid_ops[] = {">", ">>", "<", "<>", "<<",
		"<<<", NULL};

	i = 0;
	while (valid_ops[i])
	{
		if (!ft_strcmp(s1, valid_ops[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	tab_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

void	ft_find_cmd_size(t_token *token, t_cmd *new)
{
	size_t	redir;

	redir = 0;
	while (token && ft_strcmp(token->content, "|"))
	{
		if (token->type == OPP && !is_opp_file(token->content))
		{
			new->files_size++;
			redir += 2;
		}
		if (token->content && token->type == EXP)
			new->cmd_size += tab_len(token->content, ' ');
		else
			new->cmd_size++;
		token = token->next;
	}
	if ((new->cmd_size - redir) > 0)
		new->cmd_size = new->cmd_size - redir;
}

void	ft_initialize_index(t_index *index)
{
	index->cmd_i = 0;
	index->file_i = 0;
}

void	*ft_free(char **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}
