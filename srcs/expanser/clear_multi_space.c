#include "minishell.h"

size_t	ft_strlen_between_space(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

t_list	*ft_clear_space(char *s)
{
	t_list	*clean;
	char	*str;
	int		i;

	if (!s)
		return (ft_lstnew(NULL));
	clean = NULL;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			str = ft_calloc((ft_strlen_between_space(&s[i]) + 1), sizeof(char));
			if (!str)
				return (NULL);		//////////
			ft_strlcpy(str, &s[i], (ft_strlen_between_space(&s[i]) + 1));
			// printf("str clear space [%s]\n", str);
			ft_lstadd_back(&clean, ft_lstnew(str));
			i += ft_strlen_between_space(&s[i]);
		}
	}
	return (clean);
}

char	*clear_string_space(char *s)
{
	t_list	*list;
	char	*dest;

	list = ft_clear_space(s);
	dest = ft_joined_space_list(list, NULL);
	ft_lstclear(&list, &del_content);
	// ft_free(&s);
	return (dest);
}