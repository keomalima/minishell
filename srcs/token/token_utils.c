/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:14 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:47:15 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	is_val_opp(const char *str_ptr, const char *end_ptr)
{
	size_t		len;
	int			i;
	const char	*valid_ops[] = {">", ">>", "<", "<>", "<<",
		"<<<", "|", "||", "&", "&&", NULL};

	i = 0;
	len = end_ptr - str_ptr + 1;
	while (valid_ops[i])
	{
		if (!ft_strncmp(str_ptr, valid_ops[i], len))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strchr_set(char *set, int c)
{
	while (*set)
	{
		if (c == *set)
			return (set);
		set++;
	}
	return (NULL);
}
