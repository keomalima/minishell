/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_joined_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:18 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 15:47:13 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_add_spaces(const char *s, size_t *len, t_list *current)
{
	if (*len > 0 && s && *s && s[0] && ft_isspace(s[0]))
		*len += 1;
	if (*len > 0 && s && *s && s[ft_strlen(s) - 1]
		&& ft_isspace(s[ft_strlen(s) - 1]) && current->next)
		*len += 1;
}

static size_t	ft_strlen_final_joined(t_expand *expand, int *empty, int hd)
{
	t_list	*current;
	size_t	len;
	char	*clear_space;

	current = expand->exp_list;
	len = 0;
	while (current)
	{
		if (current->content)
			*empty += 1;
		if (hd != 1 && (current->content
				&& ft_isquote(((char *)current->content)[0])))
			len += (ft_strlen(current->content) - 2);
		else if (hd == 2)
			len += ft_strlen(current->content);
		else
		{
			clear_space = clear_string_space(current->content, expand);
			len += ft_strlen(clear_space);
			handle_add_spaces(((char *)current->content), &len, current);
			ft_free(&clear_space);
		}
		current = current->next;
	}
	return (len);
}

static void	ft_fill_final_joined(t_expand *expand, char *dest, int hd)
{
	t_list	*current;
	char	*cs;
	char	*s;

	current = expand->exp_list;
	while (current)
	{
		s = current->content;
		if (hd != 1 && (s && ft_isquote(s[0])))
			ft_strlcpy(&dest[ft_strlen(dest)], &s[1], ft_strlen(s) - 1);
		else if (hd == 2)
			ft_strlcpy(&dest[ft_strlen(dest)], s, (ft_strlen(s) + 1));
		else
		{
			cs = clear_string_space(s, expand);
			if (dest && *dest && s && s[0] && ft_isspace(s[0]))
				dest[ft_strlen(dest)] = ' ';
			ft_strlcpy(&dest[ft_strlen(dest)], cs, (ft_strlen(cs) + 1));
			if (dest && *dest && s && *s && s[ft_strlen(s) - 1]
				&& ft_isspace(s[ft_strlen(s) - 1]) && current->next)
				dest[ft_strlen(dest)] = ' ';
			ft_free(&cs);
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
