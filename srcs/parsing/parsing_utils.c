#include "minishell.h"

void	*ft_free(char **data)
{
	if (*data)
		free(*data);
	*data = NULL;
	return (NULL);
}


