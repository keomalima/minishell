/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:46:16 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:46:17 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_clean_quote_string(char *s, t_expand *expand)
{
	char	*dest;

	if (!s)
		return (NULL);
	dest = ft_calloc((ft_strlen(s) - 2 + 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	ft_strlcpy(dest, &s[1], ft_strlen(&s[1]));
	return (dest);
}

char	*ft_handle_quote(char *s, t_expand *expand)
{
	char	*dest;

	if (s && *s && *s == '\"')
		dest = ft_clean_quote_string(s, expand);
	else
	{
		dest = ft_strdup(s);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	return (dest);
}
