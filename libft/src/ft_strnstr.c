/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)hay);
	while (*(hay + i) && len > i)
	{
		j = 0;
		while (*(hay + i + j) && len > i + j && *(hay + i + j) == *(needle + j))
			j++;
		if (!*(needle + j))
			return ((char *)(hay + i));
		i++;
	}
	return (NULL);
}
