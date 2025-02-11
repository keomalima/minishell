#include "minishell.h"

void	here_doc(t_ms *ms, char *limiter)
{
	char	*str;

	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (!str)
			exit_handler(ms, 1);
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			free(str);
			return ;
		}
		free(str);
	}
}
