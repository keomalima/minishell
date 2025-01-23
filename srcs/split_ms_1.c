#include "../includes/minishell.h"

int is_quote(char c)
{
	if (c == 39 || c == 34)
		return (1);
	return (0);
}

size_t	count_words_ms(char *s)
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
		nb_word++;
		if (!is_quote(s[i]))
		{
			while (s[i] && s[i] != ' ')
				i++;
		}
		else
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

char	*ft_strdup_ms(char *s, size_t i)
{
	size_t	len;
	size_t	j;
	char	*str;

	j = i;
	len = 0;
	while (s[j] && s[j] != ' ')
	{
		if (!is_quote(s[j]))
			len++;
		j++;
	}
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
	{
		if (!is_quote(s[i]))
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strdup_quote_ms(char *s, char quote, size_t i)
{
	size_t	len;
	size_t	j;
	char	*str;

	len = 0;
	j = i;
	while (s[j] && s[j + 1] && (s[j] != quote || (s[j] == quote && s[j + 1] != ' ')))
	{
		if (s[j] != quote)
			len++;
		j++;
	}
	str = malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (j < len)
	{
		if (s[i] != quote)
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

int	fill_in_case_quote(const char *s, char ***tab, size_t *i, size_t *k)
{
	char quote;
	
	quote = s[*i];
	*i += 1;
	if (s[*i] == quote)
	{
		(*tab)[*k] = ft_strdup("");
		if (!(*tab)[*k])
			return (0);
		*i += 1;
	}
	else
	{
		(*tab)[*k] = ft_strdup_quote_ms((char *)s, quote, *i);
		if (!(*tab)[*k])
			return (0);
		while (s[*i] && (s[*i] != quote || (s[*i] == quote && s[*i + 1] != ' ')))
			*i += 1;
		*i += 1;
	}
	return (1);
}

int	fill_split_ms(char ***tab, size_t *k, char *s)
{
	size_t	i;

	i = 0;
	while (*k < count_words_ms((char *)s))
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (is_quote(s[i]) && s[i + 1])
		{
			if (!fill_in_case_quote(s, tab, &i, k))
				return (0);
		}
		else
		{
			(*tab)[*k] = ft_strdup_ms((char *)s, i);
			if (!(*tab)[*k])
				return (0);
			while (s[i] && s[i] != ' ')
				i++;
		}
		*k += 1;
	}
	(*tab)[*k] = NULL;
	return (1);
}
