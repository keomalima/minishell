#include "minishell.h"

static char	*clean_quote(char *s)
{
	char	*dest;

	dest = ft_calloc((ft_strlen(s) - 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[1], (ft_strlen(s) - 1));
	ft_free(&s);
	return (dest);
}

static char	**ft_clear_n_expand(char **cut, t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cut[i])
	{
		if (cut[i][0] && ft_isquote(cut[i][0]))
		{
			if (cut[i][0] == '\"' && ft_count_exp(cut[i]) > 0)
				cut[i] = expand(clean_quote(cut[i]), ms, '\"', cmd);
			else
				cut[i] = clean_quote(cut[i]);
		}
		else if (ft_count_exp(cut[i]) > 0)
			cut[i] = expand(cut[i], ms, 0, cmd);
		if (!cut[i])
		{
			free_split(cut);
			exit_handler(ms, 12);
		}
		i++;
	}
	return (cut);
}

size_t	ft_count_cut(char **cut)
{
	size_t	i;

	i = 0;
	while (cut[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_multi_space(char **cut)
{
	size_t	len;
	size_t		i;
	char	*dest;

	len = 0;
	i = 0;
	while (cut[i])
	{
		len = len + ft_strlen(cut[i]);
		i++;
	}
	if (cut[0] && cut[0][0] == ' ')
		len--;
	if (cut[i - 1] && cut[i - 1][ft_strlen(cut[i - 1]) - 1] == ' ')
		len--;
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (cut[i])
	{
		len = 0;
		if (cut[0] && cut[0][0] == ' ')
			len++;
		if ((i == ft_count_cut(cut) - 1) && cut[i][ft_strlen(cut[i]) - 1] == ' ')
			ft_strlcpy(&dest[ft_strlen(dest)], &cut[i][len], (ft_strlen(&cut[i][len])));
		else
			ft_strlcpy(&dest[ft_strlen(dest)], &cut[i][len], (ft_strlen(&cut[i][len]) + 1));
		i++;
	}
	return (dest);
}


char	*ft_translate(char *s, t_ms *ms, t_cmd *cmd)
{
	char	*ret;
	t_list	*arg;

	ft_


	return (ret);
}
