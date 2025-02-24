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
			exit_handler(ms, 12);
		ft_lstadd_back(&list, new);
	}

	return (list);
}


char	*ft_translate(char *s, t_ms *ms, t_cmd *cmd)
{
	char	*ret;
	t_list	*list;
	// t_list	*current;

	list = ft_transform_into_list(s, ms);
	if (!list)
		exit_handler(ms, 1);

	// current = list;
	// while (current)
	// {
	// 	printf(yellow"list -> %s\n"RESET, (char *)current->content);
	// 	current = current->next;
	// }

	list = ft_expanded_list(list, ms);
	// current = list;
	// while (current)
	// {
	// 	printf(green"list -> %s\n"RESET, (char *)current->content);
	// 	current = current->next;
	// }
	ret = ft_joined_list(list, ms);
	ft_lstclear(&list, &del_content);
	// printf(red"rest = [%s]\n"RESET, ret);

	ft_free(&s);
	(void)cmd;
	return (ret);
}
