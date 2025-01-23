#ifndef MINISHELL_H
# define MINISHELL_H

#define RED		"\033[1;31m"
#define red		"\033[0;31m"
#define GREEN	"\033[1;32m"
#define green	"\033[0;32m"
#define YELLOW	"\033[1;33m"
#define yellow	"\033[0;33m"
#define BLUE	"\033[1;34m"
#define blue	"\033[0;34m"
#define PURPLE	"\033[1;35m"
#define Purple	"\033[0;35m"
#define RESET   "\033[0m"

# include "libft.h"
# include <stdio.h>
# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
	COMMAND,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_APPEND,
	FILE_NAME,
	PIPE,
	ARGUMENT,
	PATH,
}			e_type;

typedef struct s_token
{
	char	*word;
	e_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

// MINISHELL UTILS
int	ft_strcmp(const char *s1, const char *s2);
void	*ft_free(void *data);

// SPLIT MINISHELL
char	**ft_split_ms(char const *s);

// PARSING
void	parse_lex(t_token **token_list, char **split);

// FT_LIST
void	ft_lstadd_back_ms(t_token **token_list, t_token *new);
t_token	*ft_lstlast_ms(t_token *lst);
t_token *create_new_token(char *str);
void	ft_lstclear_ms(t_token **lst, void (*del)(void *));
void	del_content(void *content);

// PRINT TEST
void print_list(t_token *list);
void print_split(char **split);

#endif
