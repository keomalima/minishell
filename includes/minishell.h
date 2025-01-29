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

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include <readline/readline.h>
# include <sys/wait.h>
# include <readline/history.h>

typedef enum	e_type
{
	START,
	CMD,
	OPP,
	SQ,
	DQ,
	END
}				t_type;

typedef enum	e_redir
{
	UNDEFINED,
	OUT_TRUNC,
	OUT_APPEND,
	PIPE
}				t_redir;

typedef struct		s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct 	s_lexer
{
	t_type		state;
	const char	*str_start;
	const char	*str_ptr;
	int			quote_open;
}				t_lexer;

typedef struct s_cmd
{
	char			**cmd;
	int				cmd_size;
	char			*infile;
	char			*outfile;
	t_redir			redir;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_exec
{
	int		cmd_count;
	int		here_doc;
	char	**env;
	char	**cmd;
	int		pipe_fd[2][2];
	pid_t	*child_pids;
}				t_exec;

typedef struct s_ms
{
	struct s_lexer	lexer;
	struct s_token	*token;
	struct s_cmd	*cmd;
	struct s_exec	exec;
}				t_ms;

/******************    TOKENIZER    ******************/
void	create_tokens(char *input, t_ms *ms);
t_token	*ft_lstnew_ms(t_ms *ms, char *content);
t_token	*ft_lstlast_ms(t_token *lst);
void	ft_lstadd_back_ms(t_token **lst, t_token *new);
char	*ft_strndup_ms(t_ms *ms);
char	*ft_strchr_set(char *set, int c);
void	exit_handler(t_ms *ms, int exit_code);
char	*type_to_string(t_type type);



/******************    EXPANSER    ******************/
char *get_var(char *s);


/******************    PARSER    ******************/
// PARSING UTILS
int		ft_strcmp(const char *s1, const char *s2);
int 	ft_isspaces(char c);
void	*ft_free(char **data);
// PARSING
void parse_cmd(t_ms *ms);
// FT_LIST_CMD
t_cmd *ft_lst_new_cmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new);

/******************    EXEC    ******************/
void	exec_cmd(t_ms *ms);
// EXEC UTILS
int	ft_cmd_count(t_ms *ms);
void	initialize_variables(t_ms *ms);
char	**parse_arg(t_cmd *cmd, t_ms *ms);
void	free_split(char **arr);
void	close_fd(t_ms *ms, int *fd);
void	close_all_fds(t_ms *ms);

/******************    TESTER    ******************/
// PRINT TEST
void 	print_token(t_token *list);
void 	print_split(char **split);
void 	print_cmd(t_cmd *list);

#endif
