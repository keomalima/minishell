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

char	*ft_translate(char *s, t_ms *ms, t_cmd *cmd)
{
	char	*ret;
	char	**cut;

	cut = ft_cut_string(s, ms);
	size_t i = 0;
	while (cut[i])
	{
		printf(green"%zu [%s]\n"RESET, i, cut[i]);
		i++;
	}
	cut = ft_clear_n_expand(cut, ms, cmd);
	i = 0;
	while (cut[i])
	{
		printf(blue"%zu [%s]\n"RESET, i, cut[i]);
		i++;
	}
	ret = ft_strjoin_multi(cut);
	// printf(blue"join : [%s]\n"RESET, ret);
	free_split(cut);
	ft_free(&s);
	return (ret);
}
