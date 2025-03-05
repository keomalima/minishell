#include "minishell.h"

static void	exit_program(t_ms *ms, int exit_code)
{
	free_split(ms->env);
	clean_ms(ms, 2);
	exit(exit_code);
}

static int	is_str_num(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (ft_isdigit(*s))
			return (1);
		s++;
	}
	return (0);
}

static int	parse_and_validate_args(t_ms *ms, t_cmd *cmd, int *num_arg)
{
	int	i;

	i = 1;
	while (cmd->cmd[i])
	{
		if (is_str_num(cmd->cmd[i]))
			(*num_arg)++;
		if ((!is_str_num(cmd->cmd[i]) && *num_arg > 0) || *num_arg > 1)
		{
			ft_print_error("minishell: exit: too many arguments\n", NULL, NULL);
			if (ms->exec->cmd_count == 1)
				ms->exit_status = 1;
			else
				exit_program(ms, 1);
			return (0);
		}
		else if (!is_str_num(cmd->cmd[i]))
		{
			ft_print_error("minishell: exit: ",
				cmd->cmd[i], ": numeric argument required\n");
			exit_program(ms, 2);
		}
		i++;
	}
	return (1);
}

void	exit_command(t_ms *ms, t_cmd *cmd)
{
	int	num_arg;

	num_arg = 0;
	if (ms->exec->cmd_count == 1)
		printf("exit\n");
	if (parse_and_validate_args(ms, cmd, &num_arg))
	{
		if (num_arg > 0)
			exit_program(ms, ft_atoi(cmd->cmd[1]));
		exit_program(ms, 0);
	}
}
