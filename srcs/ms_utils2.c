/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:32 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:47:33 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putstr_fd(s3, 2);
}

static int	ft_is_special_cmd(char *big, char *little)
{
	size_t	i;

	i = 0;
	while (big[i] && big[i] == ' ')
		i++;
	if (ft_strncmp(&big[i], little, ft_strlen(little)) == 0
		&& ((&big[i])[ft_strlen(little)] == ' '
		|| (&big[i])[ft_strlen(little)] == 0))
		return (1);
	return (0);
}

int	handle_key(char *rl)
{
	if (ft_is_special_cmd(rl, "clear"))
	{
		printf("\033[H\033[J");
		return (1);
	}
	else if (ft_is_special_cmd(rl, "!") || ft_is_special_cmd(rl, ":")
		|| ft_is_special_cmd(rl, "~"))
		return (1);
	return (0);
}

void	sigint_handler(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
