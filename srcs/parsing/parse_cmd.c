#include "minishell.h"

int	count_words(char *str)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '\'' ||)
		{
			word++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			word++;
			while (*str != '"')
				str++;
		}
		if (!ft_isspace(*str))
		{
			word++;
			while (!ft_isspace(*str))
				str++;
		}
		str++;
	}
	return (word);
}
