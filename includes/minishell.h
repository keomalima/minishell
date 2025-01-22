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
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	START,
	CMD,
	OPP,
	SQ,
	DQ,
	END
}				t_type;

typedef struct s_token
{
	char			*cmd;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_type		state;
	const char	*str_start;
	const char	*str_ptr;
	int			quote_open;
}				t_lexer;

typedef struct s_ms
{
	struct s_lexer	lexer;
	struct s_token	*token;
}				t_ms;

void	create_tokens(char *input, t_ms *ms);
t_token	*ft_lstnew_ms(t_ms *ms, char *content);
t_token	*ft_lstlast_ms(t_token *lst);
void	ft_lstadd_back_ms(t_token **lst, t_token *new);
char	*ft_strndup_ms(t_ms *ms);
char	*ft_strchr_set(char *set, int c);
void	exit_handler(t_ms *ms, int exit_code);
char	*type_to_string(t_type type);

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

// PARSING
void	parse(t_token **token_list, char **split);

// FT_LIST
void	ft_lstadd_back_ms(t_token **token_list, t_token *new);
t_token	*ft_lstlast_ms(t_token *lst);
t_token *create_new_token(char *str);
void	ft_lstclear_ms(t_token **lst, void (*del)(void *));
void	del_content(void *content);


#endif
