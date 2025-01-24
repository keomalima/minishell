#include "../includes/minishell.h"


size_t	ft_count_words_ms(char *s)
{
	size_t	nb_word;
	size_t	i;
	char	quote;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i])
			nb_word++;
		if (s[i] && !ft_is_quote(s[i]))
		{
			while (s[i] && s[i] != ' ')
			{
				if (ft_is_quote(s[i]))
				{
					quote = s[i++];
					while (s[i] && s[i] != quote)
						i++;
					i++;
				}
				else
					i++;
			}
		}
		else if (s[i])
		{
			quote = s[i];
			while (s[i])
			{
				i++;
				if (s[i] == quote && s[i + 1] == ' ')
				{
					i++;
					break;
				}
			}
		}
	}
	return (nb_word);
}

char	*ft_strdup_ms(char *s, size_t *i)
{
	size_t	len;
	size_t	j;
	char	*str;
	char	quote;

	j = *i;
	while (s[j] && s[j] != ' ')
	{
		if (ft_is_quote(s[j]))
		{
			quote = s[j++];
			while (s[j] && s[j] != quote)
				j++;
			if (s[j])
				j++;
		}
		else
			j++;
	}
	len = j - *i;
	str = ft_calloc ((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
		str[j++] = s[(*i)++];
	return (str);
}

char	*ft_strdup_quote_ms(char *s, char quote, size_t *i)
{
	size_t	len;
	size_t	j;
	char	*str;

	j = *i;
	while (s[j] && s[j + 1] && (s[j] != quote || (s[j] == quote && s[j + 1] != ' ')))
		j++;
	if (s[j])
		j++;
	len = j - *i + 1;
	str = ft_calloc ((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	*i -= 1;
	while (j < len)
	{
		str[j] = s[*i];
		*i = *i + 1;
		j++;
	}
	return (str);
}
