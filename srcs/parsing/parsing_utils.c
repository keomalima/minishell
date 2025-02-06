#include "minishell.h"

void	*ft_free(char **data)
{
	if (data && *data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}
