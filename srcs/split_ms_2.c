#include "../includes/minishell.h"

size_t	ft_count_words_ms(char *s);
char	*ft_strdup_ms(char *s, size_t *i);
char	*ft_strdup_quote_ms(char *s, char quote, size_t *i);

char	**clear_split_ms(char **tab, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		ft_free(&tab[i]);
		i++;
	}
	ft_free(tab);
	tab = NULL;
	return (tab);
}

int	is_full_space(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == 0)
		return (1);
	return (0);
}

int	fill_in_case_quote(const char *s, char ***tab, size_t *i, size_t *k)
{
	char quote;
	
	quote = s[*i];
	*i += 1;
	if (s[*i] && s[*i] == quote)
	{
		(*tab)[*k] = ft_strdup("");
		if (!(*tab)[*k])
			return (0);
		*i += 1;
	}
	else
	{
		(*tab)[*k] = ft_strdup_quote_ms((char *)s, quote, i);
		if (!(*tab)[*k])
			return (0);
		*i += 1;
	}
	return (1);
}

int	populate_split(char ***tab, size_t *k, char *s)
{
	size_t	i;

	i = 0;
	while (*k < ft_count_words_ms((char *)s))
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (ft_is_quote(s[i]))
		{
			if (!fill_in_case_quote(s, tab, &i, k))
				return (0);
		}
		else
		{
			(*tab)[*k] = ft_strdup_ms((char *)s, &i);
			if (!(*tab)[*k])
				return (0);
		}
		*k += 1;
	}
	return (1);
}

char	**ft_split_ms(char const *s)
{
	size_t	k;
	char	**tab;

	if (is_full_space(s))
	{
		tab = malloc(1 * sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = ft_strdup(s);
		if (!tab[0])
			return (ft_free(tab));
		return (tab);
	}
	printf(yellow"nb_words = %zu\n"RESET, ft_count_words_ms((char *)s));
	tab = ft_calloc ((ft_count_words_ms((char *)s) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	k = 0;
	if (!populate_split(&tab, &k, (char *)s))
		clear_split_ms(tab, k);
	return (tab);
}

