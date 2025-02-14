#include "minishell.h"

size_t	ft_count_string(char *s)
{
	size_t	count;
	size_t	i;
	char	quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i];
				i++;
				while (s[i] && s[i] != quote)
					i++;
				if (s[i])
					i++;
			}
			else
			{
				while (s[i] && (s[i] != '$' && s[i] != '\'' && s[i] != '\"'))
					i++;
			}
		}
		else if (s[i] == '\"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] && s[i] != quote)
				i++;
			if (s[i])
				i++;
		}
		else
		{
			while (s[i] && (s[i] != '$' && s[i] != '\'' && s[i] != '\"'))
				i++;
		}
		count++;
	}
	return (count);
}

size_t	ft_strlen_trans(char *s, int i)
{
	size_t	j;
	char	quote;

	j = i;
	if (s[j] == '$')
	{
		j++;
		if (s[j] == '\'' || s[j] == '\"')
		{
			quote = s[j];
			j++;
			while (s[j] && s[j] != quote)
				j++;
			j++;
		}
		else
		{
			while (s[j] && (s[j] != '$' && s[j] != '\'' && s[j] != '\"'))
				j++;
		}
	}
	else if (s[j] == '\"' || s[j] == '\'')
	{
		quote = s[j];
		j++;
		while (s[j] && s[j] != quote)
			j++;
		j++;
	}
	else
	{
		while (s[j] && (s[j] != '$' && s[j] != '\'' && s[j] != '\"'))
			j++;
	}
	return (j - i);
}

char	*ft_strdup_trans(char *s, size_t *i)
{
	char	*dest;
	size_t	len;

	len = ft_strlen_trans(s, *i);
	// printf("len word = %zu\n", len);
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
	size_t j;
	char	**cut;

	//printf("nb word = %zu\n", ft_count_string(s));
	cut = ft_calloc((ft_count_string(s) + 1), sizeof(char *));
	if (!cut)
		exit_handler(ms, 12);
	j = 0;
	i = 0;
	while (i < ft_count_string(s))
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
