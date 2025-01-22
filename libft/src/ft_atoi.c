/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:30:19 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	nb;

	nb = 0;
	sign = 1;
	while ((*(str) >= '\t' && *(str) <= '\r') || *(str) == ' ')
		str++;
	if (*(str) == '-' || *(str) == '+')
	{
		if (*(str) == '-')
			sign *= -1;
		str++;
	}
	while (*(str) >= '0' && *(str) <= '9')
	{
		if (nb > (LONG_MAX - (*(str) - '0')) / 10)
			if (sign == 1)
				return (-1);
		nb = (nb * 10) + *(str) - '0';
		str++;
	}
	nb *= sign;
	if (nb < INT_MIN || nb > INT_MAX)
		return (-1);
	return ((int)nb);
}
