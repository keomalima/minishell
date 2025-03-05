/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:02:15 by kricci-d          #+#    #+#             */
/*   Updated: 2025/03/05 10:12:37 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	is_delim(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static void	free_tab(char **tab, int index)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	tab_len(char const *s, const char *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && is_delim(*s, set))
			s++;
		if (*s)
		{
			count++;
			while (*s && !is_delim(*s, set))
				s++;
		}
	}
	return (count);
}

static char	*fill_str(const char *s, const char *set)
{
	int		i;
	int		str_len;
	char	*str;

	str_len = 0;
	i = 0;
	while (s[str_len] && !is_delim(s[str_len], set))
		str_len++;
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	while (i < str_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_set(char const *s, const char *set)
{
	char	**tab;
	int		i;

	i = 0;
	if (!s || !set)
		return (NULL);
	tab = malloc(sizeof(char *) * (tab_len(s, set) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (!is_delim(*s, set))
		{
			tab[i] = fill_str(s, set);
			if (!tab[i])
				return (free_tab(tab, i), NULL);
			while (*s && !is_delim(*s, set))
				s++;
			i++;
		}
		while (*s && is_delim(*s, set))
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
