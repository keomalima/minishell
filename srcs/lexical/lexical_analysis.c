#include "minishell.h"

static size_t	is_redir(const char *content)
{
	int			i;
	const char	*valid_ops[] = {">", ">>", "<", "<>", "<<", "<<<", NULL};

	i = 0;
	while (valid_ops[i])
	{
		if (!ft_strcmp(content, valid_ops[i]))
			return (0);
		i++;
	}
	return (1);
}

void	lexical_analysis(t_ms *ms)
{
	t_token	*token;
	char	*str_err;

	token = ms->token;
	while(token)
	{
		str_err = NULL;
		if (token->type == OPP)
		{
			if (!token->prev && is_redir(token->content))
				str_err = token->content;
			else if (token->prev && token->prev->type == OPP)
				str_err = token->content;
			else if (!token->next && !is_redir(token->content))
				str_err = "newline";
		}
		if (str_err)
		{
			printf("syntax error near unexpected token `%s`\n", str_err);
			clean_ms(ms, 2);
		}
		token = token->next;
	}
}
