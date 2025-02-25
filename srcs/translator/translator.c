#include "minishell.h"

void	ft_skip_quote(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
}

static size_t	ft_strlen_trans(char *s, int k)
{
	int	i;

	i = k;
	if (s[i] == '$')
	{
		i++;
		if (ft_isquote(s[i]))
			ft_skip_quote(s, &i);
		else if (s[i] == '?')
			i++;
		else
		{
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
		}
	}
	else if (ft_isquote(s[i]))
		ft_skip_quote(s, &i);
	else
		while (s[i] && (s[i] != '$' && !ft_isquote(s[i])))
			i++;
	return (i - k);
}

static char	*ft_strdup_trans(char *s, size_t *i)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_trans(s, *i);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[*i], (len + 1));
	*i = *i + len;
	return (dest);
}

t_list	*ft_transform_into_list(char *s, t_ms *ms)
{
	size_t	i;
	t_list	*list;
	t_list	*new;

	list = NULL;
	i = 0;
	while (s[i])
	{
		new = ft_lstnew(ft_strdup_trans(s, &i));
		if (!new)
		{
			ft_lstclear(&list, &del_content);
			exit_handler(ms, 12);
		}
		ft_lstadd_back(&list, new);
	}
	return (list);
}


char	*ft_translate(char *s, t_ms *ms, t_cmd *cmd)
{
	char	*ret;
	// t_list	*list;
	t_expand	expand;

	expand.ms = ms;
	expand.exp_list = NULL;
	expand.initial_list = ft_transform_into_list(s, ms);
	// list = ft_transform_into_list(s, ms);
	if (!expand.initial_list)
		exit_handler(ms, 1);
	t_list *current = expand.initial_list;
	while (current)
	{
		printf(yellow"list -> %s\n"RESET, (char *)current->content);
		current = current->next;
	}
	expand.exp_list = ft_expanded_list(&expand);
	current = expand.exp_list;
	while (current)
	{
		printf(green"list -> %s\n"RESET, (char *)current->content);
		current = current->next;
	}
	ret = ft_joined_list_without_quote(expand.exp_list, ms);
	// ret = ft_joined_list(list, ms);
	printf(red"ret = [%s]\n"RESET, ret);
	ft_lstclear(&expand.initial_list, &del_content);
	ft_lstclear(&expand.exp_list, &del_content);

	ft_free(&s);
	(void)cmd;
	return (ret);
}
