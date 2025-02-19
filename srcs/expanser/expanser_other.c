#include "minishell.h"

char	*exp_exit_code(char *s, t_ms *ms)
{
	char	*dest;
	char	*exit_code;

	exit_code = ft_itoa(ms->exit_status);
	if (!exit_code)
		return (NULL);
	dest = ft_calloc((ft_strlen(exit_code) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, exit_code, (ft_strlen(exit_code) + 1));
	ft_free(&s);
	return (dest);
}

char	*exp_digit_variable(char *s)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s) - 2;
	dest = ft_calloc((ft_strlen(s) - 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[2], (ft_strlen(&s[2]) + 1));
	ft_free(&s);
	return (dest);
}

char	*exp_quote_variable(char *s)
{
	char	*dest;

	dest = ft_calloc((ft_strlen(s) - 2), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[2], (ft_strlen(s) - 2));
	ft_free(&s);
	return (dest);
}

char	*exp_uid(char *s)
{
	struct stat	info;
	char		*tty;
	char		*dest;

	tty = ttyname(STDIN_FILENO);
	if (tty && stat(tty, &info) == 0)
	{
		dest = ft_itoa(info.st_uid);
		if (!dest)
			return (NULL);
	}
	else
	{
		perror("Failed to retrieve UID");
		return (NULL);
	}
	ft_free(&s);
	return (dest);
}
