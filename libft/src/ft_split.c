/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:02:15 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/06 15:53:52 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	tab_len(char const *s, char c)
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

static	void	free_tab(char **tab, int index)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (index > i)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

char	*fill_str(const char *s, char c)
{
	int		i;
	int		str_len;
	char	*str;

	str_len = 0;
	while (s[str_len] && s[str_len] != c)
		str_len++;
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (tab_len(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = fill_str(s, c);
			if (!tab[i])
				return (free_tab(tab, i), NULL);
			while (*s && *s != c)
				s++;
			i++;
		}
		while (*s && *s == c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
