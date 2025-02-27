#include "minishell.h"

char	*exp_exit_code(t_expand *expand)
{
	char	*dest;
	char	*exit_code;

	exit_code = ft_itoa(expand->ms->exit_status);
	if (!exit_code)
		ft_clear_expand(expand, 12);
	dest = ft_calloc((ft_strlen(exit_code) + 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	ft_strlcpy(dest, exit_code, (ft_strlen(exit_code) + 1));
	return (dest);
}

char	*exp_uid(t_expand *expand)
{
	struct stat	info;
	char		*tty;
	char		*dest;

	tty = ttyname(STDIN_FILENO);
	if (tty && stat(tty, &info) == 0)
	{
		dest = ft_itoa(info.st_uid);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	else
	{
		perror("Failed to retrieve UID");
		return (NULL);
	}
	return (dest);
}

char	*exp_digit_variable(char *s, t_expand *expand)
{
	char	*dest;

	dest = ft_calloc((ft_strlen(s) - 1), sizeof(char));
	if (!dest)
		ft_clear_expand(expand, 12);
	ft_strlcpy(dest, &s[2], (ft_strlen(&s[2]) + 1));
	return (dest);
}

char	*exp_quote_variable(char *s, t_expand *expand)
{
	char	*dest;

	if (s[0] && s[1] && ft_isquote(s[0]) && s[0] == s[1])
	{
		dest = ft_strdup(s);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	else
	{
		dest = ft_strdup(s);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	return (dest);
}

char	*exp_valid_variable(char *s, t_expand *expand)
{
	char	*variable;
	char	*dest;

	if (!s)
		return (NULL);
	variable = ft_getenv(expand->ms, s);
	if (variable == NULL || !*variable)
		dest = NULL;
	else
	{
		dest = ft_strdup(variable);
		if (!dest)
			ft_clear_expand(expand, 12);
	}
	return (dest);
}
