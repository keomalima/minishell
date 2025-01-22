/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:06:42 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_ptr_hex_len(size_t ptr)
{
	int	i;

	i = 0;
	if (ptr == 0)
		return (3);
	while (ptr > 0)
	{
		ptr /= 16;
		i++;
	}
	return (i + 2);
}

void	ft_hex_ptr(size_t ptr)
{
	char	*hex_carac;

	hex_carac = "0123456789abcdef";
	if (ptr >= 16)
		ft_hex_ptr(ptr / 16);
	ft_putchar_fd(hex_carac[ptr % 16], 1);
}

void	ft_print_ptr(va_list arg, int *len)
{
	size_t	ptr;

	ptr = va_arg(arg, size_t);
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		(*len) += 5;
		return ;
	}
	(*len) += ft_ptr_hex_len(ptr);
	ft_putstr_fd("0x", 1);
	ft_hex_ptr(ptr);
}
