/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lthan <lthan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:45:03 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 10:45:04 by lthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_var(t_var **env_var)
{
	int	i;

	i = 0;
	while (env_var[i])
	{
		ft_free(&env_var[i]->name);
		ft_free(&env_var[i]->value);
		free(env_var[i]);
		env_var[i] = NULL;
		i++;
	}
	free(env_var);
	env_var = NULL;
}

void	ft_builtins_exit(t_ms *ms, t_var **env_var, int exit_code)
{
	errno = 0;
	if (env_var)
		clean_var(env_var);
	if (exit_code == 12 || ms->exec->cmd_count > 1)
		exit_handler(ms, exit_code);
}
