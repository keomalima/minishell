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
}	t_token;

typedef struct s_cmd
{
	char	**cmd;
	char	*infile;
	char	*outfile;
	t_redir	redir_type;
	struct s_token	*next;
}	t_cmd;




// PARSING UTILS
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_free(char **data);
char	*ft_strndup_ms(char *s, t_type type);
char 	*ft_strchr_set(char *s, char *set);

// PARSING
void parse_cmd(t_cmd *cmd_list, t_token *token_list);

// FT_LIST_TOKEN
void	ft_lstadd_back_ms(t_token **token_list, t_token *new);
t_token	*ft_lstlast_ms(t_token *lst);
t_token *create_new_token(char *str);
void	ft_lstclear_ms(t_token **lst, void (*del)(void *));
void	del_content(void *content);

// FT_LIST_CMD
t_cmd *ft_lst_new_cmd(void);

// PRINT TEST
void 	print_list(t_token *list);
void 	print_split(char **split);

#endif
