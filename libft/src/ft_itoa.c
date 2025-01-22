/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:57:24 by kricci-d          #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	num_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	populate_str(int n, char *str, int len)
{
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[--len] = '8';
			n /= -10;
		}
		else
			n *= -1;
	}
	while (n > 9)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	str[--len] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		str_len;

	str_len = num_len(n);
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	populate_str(n, str, str_len);
	return (str);
}
