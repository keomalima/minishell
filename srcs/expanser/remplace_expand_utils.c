#include "minishell.h"

char	*exp_exit_code(char *str, t_expand *expand, t_exp_utils *util)
{
	char	*exit_code;

	exit_code = ft_itoa(expand->ms->exit_status);
	if (!exit_code)
		ft_handle_expand_alloc_failure(expand, util, str);
	return (exit_code);
}

char	*exp_uid(char *str, t_expand *expand, t_exp_utils *util)
{
	struct stat	info;
	char		*tty;
	char		*dest;

	tty = ttyname(STDIN_FILENO);
	if (tty && stat(tty, &info) == 0)
	{
		dest = ft_itoa(info.st_uid);
		if (!dest)
			ft_handle_expand_alloc_failure(expand, util, str);
	}
	else
	{
		perror("Failed to retrieve UID");
		return (NULL);
	}
	return (dest);
}

char    *exp_digit_variable(char *str, t_expand *expand, t_exp_utils *util)
{
    char    *dest;

    if (ft_strlen(str) == 1)
        return (NULL);
    dest = ft_calloc(ft_strlen(str), sizeof(char));
    if (!dest)
		ft_handle_expand_alloc_failure(expand, util, str);
    ft_strlcpy(dest, &str[1], ft_strlen(str));
    return (dest);
}

char	*exp_quote_variable(char *str, t_expand *expand, t_exp_utils *util)
{
	char	*dest;
	char	*s;

	printf("str [%s]\n", str);
	s = str + 1;
	if (s[0] && s[1] && ft_isquote(s[0]) && s[0] == s[1])
	{
		dest = ft_strdup(s);
		if (!dest)
			ft_handle_expand_alloc_failure(expand, util, str);

	}
	else
	{
		dest = ft_strdup(str);
		if (!dest)
			ft_handle_expand_alloc_failure(expand, util, str);

	}
	return (dest);
}

char	*exp_valid_variable(char *str, t_expand *expand, t_exp_utils *util)
{
	char	*variable;
	char	*dest;
	char	*s;

	s= str + 1;
	if (!s)
		return (NULL);
	variable = ft_getenv(expand->ms, s);
	if (variable == NULL || !*variable)
		dest = NULL;
	else
	{
		dest = ft_strdup(variable);
		if (!dest)
			ft_handle_expand_alloc_failure(expand, util, str);
	}
	return (dest);
}
