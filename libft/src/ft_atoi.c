/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:30:19 by keomalima         #+#    #+#             */
/*   Updated: 2025/03/05 17:22:15 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_strtol(const char *str, int *sign)
{
	long	nb;

	nb = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (nb > LONG_MAX / 10 || (nb == LONG_MAX / 10
				&& (*str - '0') > LONG_MAX % 10))
		{
			if (*sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nb;

	sign = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = ft_strtol(str, &sign);
	if (nb == LONG_MAX)
		return (-1);
	if (nb == LONG_MIN)
		return (0);
	return ((int)(nb * sign));
}
