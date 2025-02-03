#include "minishell.h"

char	*exp_valid_variable(char *s, t_ms *ms)
{
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s, ms);
	exp.env_var = getenv(exp.extract);
	exp.size = ft_strlen_exp(s) - ft_strlen_exp(exp.extract)
		+ ft_strlen_exp(exp.env_var) - 1;
	dest = ft_calloc((exp.size + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&exp.extract);
		exit_handler(ms, 12);
	}
	ft_fill_exp(&dest, exp);
	ft_free(&s);
	ft_free(&exp.extract);
	return (dest);
}

char	*exp_digit_variable(char *s, t_ms *ms)
{
	char	*src;
	char	*tmp;
	char	*dest;
	size_t	len;

	tmp = ft_strchr(s, '$') + 1;
	while (!ft_isdigit(*tmp))
		tmp = ft_strchr(tmp, '$') + 1;
	src = s;
	len = ft_strlen_exp(src) - ft_strlen_exp(tmp) - 1;
	while (*tmp && ft_isdigit(*tmp))
		tmp++;
	len = len + ft_strlen_exp(tmp);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		exit_handler(ms, 12);
	len = 0;
	while (*src && !(*src == '$' && ft_isalnum(*(src + 1))))
		dest[len++] = *src++;
	while (*tmp)
		dest[len++] = *tmp++;
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

	tmp = ft_strchr(s, '$') + 1;
	while (*tmp != '?')
		tmp = ft_strchr(tmp, '$') + 1;
	
	exit_code = ft_itoa(ms->exit_status);
	if (!exit_code)
		exit_handler(ms, 12);
	src = s;
	len = ft_strlen_exp(src) - ft_strlen_exp(tmp) - 1;
	tmp++;
	len = len + ft_strlen_exp(tmp) + ft_strlen_exp(exit_code);
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

size_t	ft_count_exp(char *s)
{
	char	*tmp;
	size_t	count_exp;

	count_exp = 0;
	tmp = ft_strchr(s, '$');
	while (tmp)
	{
		if (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '?')
			count_exp++;
		tmp = ft_strchr((tmp + 1), '$');
	}
	printf(RED"Count = %zu\n"RESET, count_exp);
	return (count_exp);
}

char	*expanser(char *s, t_ms *ms)
{
	char	*str;
	size_t	count_exp;

	str = s;
	count_exp = ft_count_exp(s);
	while (count_exp > 0)
	{
		str = ft_strchr(s, '$');
		while (!ft_isalnum(*(str + 1)) && *(str + 1) != '?')
			str = ft_strchr((str + 1), '$');
		if (*(str + 1) == '?')
			s = exp_exit_code(s, ms);
		else if (ft_isalpha(*(str + 1)))
			s = exp_valid_variable(s, ms);
		else if (ft_isdigit(*(str + 1)))
			s = exp_digit_variable(s, ms);
		count_exp--;
	}
	return (s);
}
