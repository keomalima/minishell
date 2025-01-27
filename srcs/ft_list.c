#include "../includes/minishell.h"

t_token	*ft_lstnew_ms(char *content, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*ft_lstlast_ms(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_ms(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast_ms(*lst);
		last->next = new;
	}
}

int	ft_is_set(char c, char *set)
{
	size_t	i;

	i = 0;
	while(set[i])
	{
		if (c == set[i])
		return (1);
		i++;
	}
	return (0);
}

char *ft_strchr_set(const char *s, char *set)
{
	while (*s)
	{
		if (ft_is_set(*s, set))
			return ((char *)s);
		s++;
	}
	return (NULL);
}

t_type	ft_define_state(char c)
{
	if (c == 34)
		return (IN_DOUBLE_QUOTE);
	if (c == 39)
		return (IN_SINGLE_QUOTE);
	else
		return (START);
}

size_t	ft_strlen_state(const char *s, const char *end, t_type state)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (&s[i] != end)
	{
		if (ft_define_state(s[i]) != state)
			len++;
		i++;
	}
	return (len);
}

char	*ft_strndup_ms(const char *s, const char *end, t_type state)
{
	int		len;
	char	*str;
	size_t	i;
	size_t	j;

	len = ft_strlen_state(s, end, state);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (&s[i] != end)
	{
		if (ft_define_state(s[i]) != state)
			str[j++] = s[i];
		i++;
	}
	return (str);
}
