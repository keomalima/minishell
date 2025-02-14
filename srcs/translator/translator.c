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

static char	**ft_clear_n_expand(char **cut, t_ms *ms)
{
	int	i;

	i = 0;
	while (cut[i])
	{
		if (cut[i][0] && ft_isquote(cut[i][0]))
		{
			if (cut[i][0] == '\"' && ft_count_exp(cut[i]) > 0)
				cut[i] = expand(clean_quote(cut[i]), ms);
			else
				cut[i] = clean_quote(cut[i]);
		}
		else if (ft_count_exp(cut[i]) > 0)
			cut[i] = expand(cut[i], ms);
		if (!cut[i])
		{
			free_split(cut);
			exit_handler(ms, 12);
		}
		i++;
	}
	return (cut);
}

char	*ft_translate(char *s, t_ms *ms)
{
	char	*ret;
	char	**cut;

	cut = ft_cut_string(s, ms);
	cut = ft_clear_n_expand(cut, ms);
	ret = ft_strjoin_multi(cut);
	free_split(cut);
	ft_free(&s);
	return (ret);
}
