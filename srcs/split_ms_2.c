#include "../includes/minishell.h"

size_t	count_words_ms(char *s);
int		fill_split_ms(char ***tab, size_t *k, char *s);

char	**clear_split_ms(char **tab, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		ft_free(tab[i]);
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
	tab = malloc ((count_words_ms((char *)s) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	k = 0;
	if (!fill_split_ms(&tab, &k, (char *)s))
		clear_split_ms(tab, k);
	return (tab);
}
