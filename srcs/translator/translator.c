#include "minishell.h"

char	*ft_strjoin_multi(char **cut)
{
	size_t	len;
	int		i;
	char	*dest;

	len = 0;
	i = 0;
	while (cut[i])
	{
		len = len + ft_strlen(cut[i]);
		i++;
	}
	dest = ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (NULL);
	len = 0;
	i = 0;
	while (cut[i])
	{
		ft_strlcpy(&dest[ft_strlen(dest)], cut[i], (ft_strlen(cut[i]) + 1));
		i++;
	}
	return (dest);
}

size_t	ft_strlen_except(char *s, char c)
{
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

size_t	ft_strlcpy_except(char *dst, const char *src, size_t size, char c)
{
	size_t	i;
	size_t	j;

	if (dst && src && size > 0)
	{
		i = 0;
		j = 0;
		while (size - 1 > i && src[i])
		{
			if (src[i] != c)
				dst[j++] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}


/* char	*clean_quote(char *s, char quote)
{
	char	*dest;

	dest = ft_calloc((ft_strlen_except(s, quote) + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy_except(dest, s, (ft_strlen(s) + 1), quote);
	ft_free(&s);
	return (dest);
} */

char	*clean_quote(char *s)
{
	char	*dest;

	dest = ft_calloc((ft_strlen(s) - 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, &s[1], (ft_strlen(s) - 1));
	ft_free(&s);
	return (dest);
}
char	*expand(char *s)
{
	printf("multi expansion\n");
	return (s);
}

char	**ft_clear_n_expand(char **cut, t_ms *ms)
{
	int	i;

	i = 0;
	while (cut[i])
	{
		if (cut[i][0] && (cut[i][0] == '\'' || cut[i][0] == '\"'))
		{
			if (cut[i][0] == '\"' && ft_count_exp(cut[i]) > 0)
				cut[i] = expand(clean_quote(cut[i]));
			else
				cut[i] = clean_quote(cut[i]);
			if (!cut[i])
			{
				free_split(cut);
				exit_handler(ms, 12);
			}
		}
		// if (ft_strchr(cut[i], '$'))
		// 	cut[i] = expanser(cut[i], ms);
		i++;
	}
	return (cut);
}

char	*ft_translate(char *s, t_ms *ms)
{
	char	*ret;
	char	**cut;
	int		i;

	cut = ft_cut_string(s, ms);
	
	i = 0;
	while (cut[i])
	{
		printf("(%d) [%s]\n", i, cut[i]);
		i++;
	}
	cut = ft_clear_n_expand(cut, ms);
	i = 0;
	while (cut[i])
	{
		printf("(%d) [%s]\n", i, cut[i]);
		i++;
	}
	ret = ft_strjoin_multi(cut);
	free_split(cut);
	return (ret);
}