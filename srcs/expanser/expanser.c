#include "minishell.h"

char	*exp_valid_variable(char *s, t_ms *ms)
{
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s, ms);
	exp.env_var = ft_getenv(ms, exp.extract);
	printf("env var = [%s]\n", exp.env_var);
	exp.env_var = ft_clear_space(exp.env_var, ms);
	printf("env var = [%s]\n", exp.env_var);

	exp.size = ft_strlen(s) - ft_strlen(exp.extract)
		+ ft_strlen(exp.env_var) - 1;
	dest = ft_calloc((exp.size + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&exp.extract);
		exit_handler(ms, 12);
	}
	ft_fill_exp(&dest, exp);
	ft_free(&s);
	ft_free(&exp.extract);
	ft_free(&exp.env_var);
	return (dest);
}

char	*exp_digit_variable(char *s, t_ms *ms)
{
	char	*src;
	char	*dest;
	size_t	len;

	src = s;
	len = ft_strlen(src) - 2;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		exit_handler(ms, 12);
	len = 0;
	while (*src && !(*src == '$' && ft_isalnum(*(src + 1))))
		dest[len++] = *src++;
	src +=2;
	while (*src)
		dest[len++] = *src++;
	ft_free(&s);
	return (dest);
}

char	*exp_exit_code(char *s, t_ms *ms)
{
	char	*dest;
	char	*tmp;
	char	*src;
	char	*exit_code;
	size_t	len;

	exit_code = ft_itoa(ms->exit_status);
	if (!exit_code)
		exit_handler(ms, 12);
	tmp = ft_strchr(s, '$') + 1;
	src = s;
	len = ft_strlen(src) - ft_strlen(tmp) - 1;
	tmp++;
	len = len + ft_strlen(tmp) + ft_strlen(exit_code);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		exit_handler(ms, 12);
	len = 0;
	while (*src && !(*src == '$' && *(src + 1) == '?'))
		dest[len++] = *src++;
	src = exit_code;
	while (*src)
		dest[len++] = *src++;
	while (*tmp)
		dest[len++] = *tmp++;
	ft_free(&s);
	return (dest);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

size_t	ft_count_exp(char *s)
{
	char	*tmp;
	size_t	count_exp;

	count_exp = 0;
	tmp = ft_strchr(s, '$');
	while (tmp)
	{
		if (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?' || ft_isquote(*(tmp + 1)))
			count_exp++;
		tmp = ft_strchr((tmp + 1), '$');
	}
	return (count_exp);
}

char	*expanser(char *s, t_ms *ms)
{
	char	*str;

	str = ft_strchr(s, '$');
	if (*(str + 1) == '?')
		s = exp_exit_code(s, ms);
	else if (ft_isalpha(*(str + 1)))
		s = exp_valid_variable(s, ms);
	else if (ft_isdigit(*(str + 1)))
		s = exp_digit_variable(s, ms);

	return (s);
}
