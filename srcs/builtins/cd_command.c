#include "minishell.h"

int	ft_check_valid_dir(t_ms *ms, t_cmd *cmd)
{
	struct stat	sb;

	if (stat(cmd->cmd[1], &sb) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		printf("cd: %s: Not a directory\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	if (access(cmd->cmd[1], X_OK) == -1)
	{
		printf("cd: %s: Permission denied\n", cmd->cmd[1]);
		ft_builtins_exit(ms, NULL, 1);
		return (0);
	}
	return (1);
}

char	*ft_uptaded_old_pwd(t_ms *ms, int i_new, int i_old)
{
	char	*tmp;

	tmp = ft_calloc((ft_strlen(ms->env[i_new]) + 4), sizeof(char));
	if (!tmp)
	{
		ft_builtins_exit(ms, NULL, 12);
		return (NULL);
	}
	ft_strlcpy(tmp, "OLD", 4);
	ft_strlcpy(&tmp[3], ms->env[i_new], (ft_strlen(ms->env[i_new]) + 1));
	ft_free(&ms->env[i_old]);
	return (tmp);
}

char	*ft_updated_new_pwd(t_ms *ms, int i_new, char *new_pwd)
{
	char	*tmp;

	tmp = ft_calloc((ft_strlen(new_pwd) + 5), sizeof(char));
	if (!tmp)
	{
		ft_builtins_exit(ms, NULL, 12);
		return (NULL);
	}
	ft_strlcpy(tmp, "PWD=", 5);
	ft_strlcpy(&tmp[4], new_pwd, (ft_strlen(new_pwd) + 1));
	ft_free(&ms->env[i_new]);
	return (tmp);
}

void	ft_update_pwd(t_ms *ms)
{
	char	*new_pwd;
	int		i_old;
	int		i_new;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		printf("chdir: error retrieving current directory: \
			getcwd: cannot access parent directories: \
			No such file or directory\n");
		return ;
	}
	i_old = ft_find_var("OLDPWD", ms);
	if (i_old >= 0)
	{
		i_new = ft_find_var("PWD", ms);
		if (i_new >= 0)
		{
			ms->env[i_old] = ft_uptaded_old_pwd(ms, i_new, i_old);
			if (!ms->env[i_old])
				return ;
			ms->env[i_new] = ft_updated_new_pwd(ms, i_new, new_pwd);
			if (!ms->env[i_new])
				return ;
			ft_free(&new_pwd);
		}
	}
}

void	cd_command(t_ms *ms, t_cmd *cmd)
{
	if (cmd->cmd_size > 2)
	{
		printf("cd : too many arguments\n");
		return (ft_builtins_exit(ms, NULL, 1));
	}
	if (!cmd->cmd[1] || !*cmd->cmd[1])
	{
		if (!ft_getenv(ms, "HOME"))
			printf("cd: HOME not set\n");
		if (chdir(ft_getenv(ms, "HOME")) == -1)
		{
			perror("cd");
			return (ft_builtins_exit(ms, NULL, 1));
		}
	}
	else
	{
		if (chdir(cmd->cmd[1]) == -1)
		{
			perror("cd");
			return (ft_builtins_exit(ms, NULL, 1));
		}
		ft_update_pwd(ms);
	}
	ft_builtins_exit(ms, NULL, 0);
}
