#include "minishell.h"

void	pwd_command(t_ms *ms, t_cmd *cmd)
{
	char	*pwd;

	if (cmd->cmd_size > 2)
	{
		printf("cd : too many arguments\n");
		return (ft_builtins_exit(ms, NULL, 0));
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("chdir: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
		return (ft_builtins_exit(ms, NULL, 1));
	}
	printf("%s\n", pwd);
	ft_free(&pwd);
	return (ft_builtins_exit(ms, NULL, 0));
}
