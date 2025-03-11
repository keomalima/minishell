#include "minishell.h"

static size_t	ft_strlen_final_joined(t_expand *expand, int *empty, int hd)
{
	t_list	*current;
	size_t	len;
	char	*clear_space;
	char	*s;

	current = expand->exp_list;
	len = 0;
	while (current)
	{
		s = current->content;
		if (s)
			*empty += 1;
		if (hd == 0 && (s && ft_isquote(s[0])))
			len += (ft_strlen(s) - 2);
		else
		{
			clear_space = clear_string_space(s, expand);
			len += ft_strlen(clear_space);
			if (len > 0 && s && s[0] && ft_isspace(s[0]))
				len++;
			ft_free(&clear_space);
		}
		current = current->next;
	}
	return (len);
}

static void	ft_fill_final_joined(t_expand *expand, char *dest, int hd)
{
	t_list	*current;
	char	*clear_space;
	char	*s;

	current = expand->exp_list;
	while (current)
	{
		s = current->content;
		if (hd == 0 && (s && ft_isquote(s[0])))
			ft_strlcpy(&dest[ft_strlen(dest)], &s[1], ft_strlen(s) - 1);
		else
		{
			clear_space = clear_string_space(s, expand);
			if (dest && *dest && s && s[0] && ft_isspace(s[0]))
				dest[ft_strlen(dest)] = ' ';
			ft_strlcpy(&dest[ft_strlen(dest)], clear_space,
				(ft_strlen(clear_space) + 1));
			ft_free(&clear_space);
		}
		current = current->next;
	}
}

char	*ft_joined_final_list(t_expand *expand, int hd)
{
	char	*dest;
	int		check_empty;
	size_t	len;

	check_empty = 0;
	len = ft_strlen_final_joined(expand, &check_empty, hd);
	if (check_empty == 0)
		return (NULL);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	ft_fill_final_joined(expand, dest, hd);
	return (dest);
}
