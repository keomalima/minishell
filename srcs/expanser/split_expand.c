/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:46:24 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:46:25 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_expand(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '$')
	{
		i++;
		if (s[i] && ft_isquote(s[i]))
		{
			ft_skip_quote(s, &i);
			return (i);
		}
		else if (s[i] == '?')
			i++;
		else
		{
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			return (i);
		}
	}
	else
		while (s[i] && s[i] != '$')
			i++;
	return (i);
}

char	*ft_split_expand(char *s, int *j, t_expand *expand)
{
	char	*str;
	size_t	len;

	if (!s[*j])
		len = 0;
	else
		len = ft_strlen_expand(&s[*j]);
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
	{
		ft_free(&s);
		ft_clear_expand(expand, 12);
	}
	ft_strlcpy(str, &s[*j], (len + 1));
	*j = *j + len - 1;
	return (str);
}
