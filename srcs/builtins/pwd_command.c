/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:45:57 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:45:58 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_pwd_error(void)
{
	ft_print_error("pwd: error retrieving current directory: ",
		"getcwd: cannot access parent directories: ",
		"No such file or directory\n");
}

void	pwd_command(t_ms *ms)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		ft_print_pwd_error();
		ms->exit_status = 1;
		return (ft_builtins_exit(ms, NULL, 1));
	}
	else
		ms->exit_status = 0;
	printf("%s\n", pwd);
	return (ft_builtins_exit(ms, NULL, 0));
}
