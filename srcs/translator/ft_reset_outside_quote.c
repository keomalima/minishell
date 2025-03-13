/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_outside_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:20 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:47:21 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_reset_outside_quote(char *ret, char *s, t_ms *ms)
{
	int		len;
	char	*dest;

	(void)ms;
	len = 0;
	if (s[0] && ft_isquote(s[0]))
		len++;
	if (ft_strlen(s) > 1 && ft_isquote(s[ft_strlen(s) - 1]))
		len++;
	if (len == 0)
		return (ret);
	dest = ft_calloc((len + ft_strlen(ret) + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&ret);
		return (NULL);
	}
	len = 0;
	if (s[0] && ft_isquote(s[0]))
		dest[len++] = s[0];
	ft_strlcpy(&dest[len], ret, (ft_strlen(ret) + 1));
	if (ft_strlen(s) > 1 && ft_isquote(s[ft_strlen(s) - 1]))
		dest[ft_strlen(dest)] = s[ft_strlen(s) - 1];
	ft_free(&ret);
	return (dest);
}
