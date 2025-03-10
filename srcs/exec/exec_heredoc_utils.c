#include "minishell.h"

int	ft_strcmp_here_doc(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;

	if (s1[0] == '"' || s1[0] == '\'')
		s1++;
	len = ft_strlen(s1);
	if (len > 0 && (s1[len - 1] == '"' || s1[len - 1] == '\''))
		len--;
	i = 0;
	while (i < len && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == len && !s2[i])
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_interupt(void)
{
	return (0);
}

void	sigint_here_doc(int sig)
{
	g_signal = sig;
	rl_done = 1;
}

void	sigquit_handler(void)
{
	ft_printf("minishell: warning: here-document delimited by"
		"end-of-file (wanted `EOF')\n");
}

int	is_valid_string(const char *str)
{

	if (!ft_strcmp(str, ".") || !ft_strcmp(str, "..") ||
		!ft_strcmp(str, "...") || !ft_strcmp(str, "...."))
		return (0);
	return (1);
}