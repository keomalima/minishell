#include "../includes/minishell.h"

void get_var(char *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
			i++;
		if (s[i] && s[i] == '$')
			i++;
		while (s[i] && ft_isalnum(s[i]))
		{
			i++;
			len++;
		}
	}
	printf("len = %d	|	i = %d\n", len, i);
	str = ft_calloc((len + 1), sizeof(char));
	while ()
}