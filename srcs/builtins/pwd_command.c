#include "minishell.h"

void	ft_print_cwd_error(void)
{
	printf("chdir: error retrieving current directory: ");
	printf("getcwd: cannot access parent directories: ");
	printf("No such file or directory\n");
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
	printf("%s\n", pwd);
	ft_free(&pwd);
	return (ft_builtins_exit(ms, NULL, 0));
}