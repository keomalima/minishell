/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:02:14 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_len_uns(unsigned int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_len_sig(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		if (n == INT_MIN)
			return (11);
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_print_uns(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_print_uns(n / 10, fd);
	}
	ft_putchar_fd((n % 10 + '0'), fd);
}

void	ft_print_int(char spec, va_list arg, int *len)
{
	int		nbr;

	nbr = va_arg(arg, int);
	if (spec == 'd' || spec == 'i')
	{
		(*len) += ft_len_sig(nbr);
		ft_putnbr_fd(nbr, 1);
	}
	else
	{
		(*len) += ft_len_uns((unsigned int)nbr);
		ft_print_uns((unsigned int)nbr, 1);
	}
}
