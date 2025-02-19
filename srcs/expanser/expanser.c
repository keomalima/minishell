#include "minishell.h"

static size_t	ft_strlen_expand(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '$')
	{
		i++;
		if (s[i] && ft_isquote(s[i]))
		{
			ft_skip_quote(s, &i);
			return (i);
		}
		else if (s[i] == '?')
			i++;
		else
		{
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			return (i);
		}
	}
	else
		while (s[i] && s[i] != '$')
			i++;
	return (i);
}

static char	*ft_fill_cut_expand(char *s, int *j)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_expand(&s[*j]);
	// printf("len = %zu\n", len);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[*j], (len + 1));
	*j = *j + len;
	return (dest);
}


static char	*ft_remplace_exp(char *s, t_ms *ms, char quote, int *ex)
{
	char	*str;

	str = ft_strchr(s, '$');
	if (*(str + 1) == '?')
		s = exp_exit_code(s, ms);
	else if (ft_strcmp((str + 1), "UID") == 0)
		s = exp_uid(s);
	else if (ft_isalpha(*(str + 1)))
		s = exp_valid_variable(s, ms);
	else if (ft_isdigit(*(str + 1)))
		s = exp_digit_variable(s);
	else if (ft_isquote(*(str + 1)) && quote != '\"')
		s = exp_quote_variable(s);
	else
		*ex = 0;
	return (s);
}


static char	**ft_cut_n_expand(char *s, t_ms *ms, char quote, t_cmd *cmd)
{
	char	**cut_expand;
	size_t	i;
	size_t	size;
	int		j;
	int		ex;

	size = ft_count_word_exp(s);
	cut_expand = ft_calloc((size + 1), sizeof(char *));
	if (!cut_expand)
		return (NULL);
	i = 0;
	j = 0;
	ex = 1;
	while (i < size)
	{
		cut_expand[i] = ft_fill_cut_expand(s, &j);
		if (cut_expand[i] && cut_expand[i][0] == '$')
		{
			cut_expand[i] = ft_remplace_exp(cut_expand[i], ms, quote, &ex);
			if (!cut_expand[i])
			{
				free_split(cut_expand);
				return (NULL);
			}
		}
		i++;
	}
	if (ex == 1)
		cmd->nb_expand += 1;
	return (cut_expand);
}

char	*expand(char *s, t_ms *ms, char quote, t_cmd *cmd)
{
	char	**cut_expand;
	char	*dest;

	cut_expand = ft_cut_n_expand(s, ms, quote, cmd);
	if (!cut_expand)
		return (NULL);
	// size_t i = 0;
	// while (cut_expand[i])
	// {
	// 	printf(yellow"%zu [%s]\n"RESET, i, cut_expand[i]);
	// 	i++;
	// }
	dest = ft_strjoin_multi(cut_expand);
	if (!dest)
	{
		free_split(cut_expand);
		return (NULL);
	}
	free_split(cut_expand);
	ft_free(&s);
	return (dest);
}
