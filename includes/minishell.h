#ifndef MINISHELL_H
# define MINISHELL_H

#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

# include "../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_type{
	START,
	IN_COMMAND,
	IN_OPERATOR,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	IN_VARIABLE,
	END
} t_type;

typedef struct s_token
{
	char	*cmd;
	t_type	type;
	struct s_token	*next;
}	t_token;

t_token	*ft_lstnew_ms(char *content, t_type type);
t_token	*ft_lstlast_ms(t_token *lst);
void	ft_lstadd_back_ms(t_token **lst, t_token *new);
void	finite_state_machine(char *input, t_token **list);

#endif