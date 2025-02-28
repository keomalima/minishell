#include "minishell.h"

void	ft_print_cwd_error(void)
{
	ft_print_error("chdir: error retrieving current directory: ",
		"getcwd: cannot access parent directories: ",
		"No such file or directory\n");
}

void    pwd_command(t_ms *ms)
{
	char    *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_print_cwd_error();
		return (ft_builtins_exit(ms, NULL, 1));
	}
	else
		ms->exit_status = 0;
	printf("%s\n", pwd);
	ft_free(&pwd);
	return (ft_builtins_exit(ms, NULL, 0));
}