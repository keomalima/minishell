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

typedef enum e_type{
	START,
	IN_COMMAND,
	IN_OPERATOR,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	IN_VARIABLE,
	END
} t_type;

typedef enum e_redir{
	UNDEFINED,
	OUT_TRUNC,
	OUT_APPEND,
	PIPE
} t_redir;

typedef struct s_token
{
	char	*content;
	t_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**cmd;
	int				cmd_size;
	char			*infile;
	char			*outfile;
	t_redir			redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
    struct s_lexer	*lexer;
    struct s_token	*token;
    struct s_cmd	*cmd;
}                t_ms;

// VARIABLE EXPANSION
void get_var(char *s);

// PARSING UTILS
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup_ms(char *s, t_type type);
char 	*ft_strchr_set(char *s, char *set);
int 	ft_isspaces(char c);

// PARSING
void parse_cmd(t_ms *ms);

// FT_LIST_TOKEN
void	ft_lstadd_back_token(t_token **token_list, t_token *new);
t_token	*ft_lstlast_token(t_token *lst);
t_token *create_new_token(char *str);
void	ft_lstclear_token(t_token **lst, void (*del)(void *));
void	del_content(void *content);

// FT_LIST_CMD
t_cmd *ft_lst_new_cmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new);

// PRINT TEST
void 	print_token(t_token *list);
void 	print_split(char **split);
void 	print_cmd(t_cmd *list);

#endif
