#include "minishell.h"

char	*exp_valid_variable(char *s, t_ms *ms)
{
	t_exp	exp;
	char	*dest;

	exp.src = s;
	exp.size = 0;
	exp.extract = ft_extract_var(s);
	// printf("env extract = [%s]\n", exp.extract);
	if (!exp.extract)
		return (NULL);
	exp.env_var = ft_getenv(ms, exp.extract);
	// printf("env var = [%s]\n", exp.env_var);
	exp.env_var = ft_clear_space(exp.env_var);
	// printf("clean env var = [%s]\n", exp.env_var);

	exp.size = ft_strlen(s) - ft_strlen(exp.extract) + ft_strlen(exp.env_var) - 1;
	dest = ft_calloc((exp.size + 1), sizeof(char));
	if (!dest)
	{
		ft_free(&exp.env_var);
		ft_free(&exp.extract);
		return (NULL);
	}
	ft_strlcpy(dest, exp.env_var, (ft_strlen(exp.env_var) + 1));
	// printf("dest = [%s]\n", dest);
	// ft_fill_exp(&dest, exp);
	ft_free(&s);
	ft_free(&exp.extract);
	ft_free(&exp.env_var);
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
	// printf(purple"Nb of expansion %zu\n"RESET, count_exp);
	return (count_exp);
}

char	*expanser(char *s, t_ms *ms)
{
	char	*str;

	// printf("-->Expanser\n");
	str = ft_strchr(s, '$');
	if (*(str + 1) == '?')
		s = exp_exit_code(s, ms);
	else if (ft_isalpha(*(str + 1)))
		s = exp_valid_variable(s, ms);
	else if (ft_isdigit(*(str + 1)))
		s = exp_digit_variable(s);
	else if (ft_isquote(*(str + 1)))
		s = exp_quote_variable(s);
	return (s);
}

size_t	ft_count_word_exp(char *s)
{
	int	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (ft_isquote(s[i]))
			{
				i++;
				while (s[i] && !ft_isquote(s[i]))
					i++;
				i++;
			}
			else if (s[i] == '?')
				i++;
			else
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					i++;
		}
		else
		{
			while (s[i] && s[i] != '$')
				i++;
		}
		count++;
	}
	printf(yellow"count word expand : %zu\n"RESET, count);
	return (count);
}

size_t	ft_strlen_expand(char *s)
{
	size_t	i;
	char	quote;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '$')
	{
		i++;
		if (ft_isquote(s[i]))
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			return (i + 1);
		}
		else if (s[i] == '?')
			i++;
		else
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			return (i);
	}
	while (s[i] && s[i] != '$')
		i++;
	return (i);
}

char	*ft_fill_cut_expand(char *s, int *j)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_expand(&s[*j]);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[*j], (len + 1));
	// printf(blue"dest [%s]\n"RESET, dest);
	*j = *j + len;
	return (dest);
}

char	**ft_cut_expand(char *s, t_ms *ms)
{
	size_t	count;
	char	**cut_expand;
	size_t		i;
	int		j;

	count = ft_count_word_exp(s);
	cut_expand = ft_calloc((count + 1), sizeof(char*));
	if (!cut_expand)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		cut_expand[i] = ft_fill_cut_expand(s, &j);
		if (cut_expand[i] && cut_expand[i][0] == '$')
			cut_expand[i] = expanser(cut_expand[i], ms);
		i++;
	}
	return (cut_expand);
}

char	*expand(char *s, t_ms *ms)
{
	char	**cut_expand;
	char	*dest;

	// printf("expansion\n");
	cut_expand = ft_cut_expand(s, ms);
	if (!cut_expand)
		return (NULL);
	dest = ft_strjoin_multi(cut_expand);
	(void)ms;
	ft_free(&s);
	return (dest);
}
