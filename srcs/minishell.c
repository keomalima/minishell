#include "../includes/minishell.h"

void	parse_cmd(char *cmd, t_token **head)
{
	int		i;
	char	*start;
	t_token	*current;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		if (cmd[i] == '|')
		{
			current = ft_lstnew_ms(strdup("|"), PIPE);
			i++;
		}
		else if (cmd[i] == '<')
		{
			current = ft_lstnew_ms(strdup("<"), OPERAND);
			i++;
		}
		else
		{
			start = &cmd[i];
			while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '\n')
				i++;
			current = ft_lstnew_ms(strndup(start, i - (start - cmd)), COMMAND);
		}
		if (!*head)
			*head = current;
		else
			ft_lstadd_back_ms(head, current);
	}
}