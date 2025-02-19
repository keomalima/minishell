#include "minishell.h"

void	ft_skip_quote(char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i])
		(*i)++;
}

static void	ft_count_string(char *s, size_t	*count)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] && ft_isquote(s[i]))
				ft_skip_quote(s, &i);
			else if (s[i] == '?')
				i++;
			else
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
					i++;
		}
		else if (ft_isquote(s[i]))
			ft_skip_quote(s, &i);
		else
			while (s[i] && (s[i] != '$' && !ft_isquote(s[i])))
				i++;
		(*count)++;
	}
}

static size_t	ft_strlen_trans(char *s, int k)
{
	int	i;

	i = k;
	if (s[i] == '$')
	{
		i++;
		if (ft_isquote(s[i]))
			ft_skip_quote(s, &i);
		else if (s[i] == '?')
			i++;
		else
		{
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
		}
	}
	else if (ft_isquote(s[i]))
		ft_skip_quote(s, &i);
	else
		while (s[i] && (s[i] != '$' && !ft_isquote(s[i])))
			i++;
	return (i - k);
}

static char	*ft_strdup_trans(char *s, size_t *i)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_trans(s, *i);
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[*i], (len + 1));
	*i = *i + len;
	return (dest);
}

char	**ft_cut_string(char *s, t_ms *ms)
{
	size_t	i;
	size_t	j;
	char	**cut;
	size_t	count;

	count = 0;
	ft_count_string(s, &count);
	cut = ft_calloc((count + 1), sizeof(char *));
	if (!cut)
		exit_handler(ms, 12);
	j = 0;
	i = 0;
	while (i < count)
	{
		cut[i] = ft_strdup_trans(s, &j);
		if (!cut[i])
		{
			free_split(cut);
			exit_handler(ms, 12);
		}
		i++;
	}
	return (cut);
}
