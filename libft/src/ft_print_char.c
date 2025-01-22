/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:59:18 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_char(char spec, va_list arg, int *len)
{
	char	c;
	char	*str;

	str = NULL;
	if (spec == 'c')
	{
		c = va_arg(arg, int);
		(*len)++;
		ft_putchar_fd(c, 1);
	}
	else
	{
		str = va_arg(arg, char *);
		if (!str)
			str = "(null)";
		(*len) += ft_strlen(str);
		ft_putstr_fd(str, 1);
	}
}
