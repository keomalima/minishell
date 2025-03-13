/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:29 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:47:30 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (0);
	else
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

char	*ft_getenv(t_ms *ms, char *str)
{
	int	i;

	if (!ms || !ms->env)
		return (NULL);
	i = 0;
	while (ms->env[i])
	{
		if (ft_strncmp(ms->env[i], str, ft_strlen(str)) == 0
			&& ms->env[i][ft_strlen(str)] == '=')
			return (&ms->env[i][ft_strlen(str) + 1]);
		i++;
	}
	return (NULL);
}

int	ft_is_only_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
