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
#define purple	"\033[0;35m"
#define RESET   "\033[0m"

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include <sys/wait.h>
#include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>

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
	int			d_quo_open;
	int			s_quo_open;
}				t_lexer;

typedef struct	s_infile
{
	char	*name;
	int		is_lim;
}				t_infile;

typedef struct	s_outfile
{
	char		*name;
	t_redir		type;
}				t_outfile;

typedef struct s_cmd
{
	char				**cmd;
	size_t				cmd_size;
	struct s_infile		**infile;
	size_t				infile_size;
	struct s_outfile	**outfile;
	size_t				outfile_size;
	t_redir				redir;
	struct s_cmd		*next;
}				t_cmd;

typedef struct s_index
{
	size_t	cmd_i;
	size_t	in_i;
	size_t	out_i;
}			t_index;

typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;

typedef struct s_exec
{
	int		cmd_count;
	char	**env;
	char	**cmd;
	int		pipe_fd[2][2];
	pid_t	*child_pids;
}				t_exec;

typedef struct s_exp
{
	char	*src;
	char	*extract;
	char	*env_var;
	size_t	size;
}				t_exp;

typedef struct s_ms
{
	struct s_lexer	lexer;
	struct s_token	*token;
	struct s_cmd	*cmd;
	struct s_exec	*exec;
	int				exit_status;
	size_t			cmd_count;
	char			**env;
	char			*lex_err;
}				t_ms;

/******************    UTILS    ******************/
int		ft_strcmp(const char *s1, const char *s2);
void	clean_ms(t_ms *ms, int exit_code);
size_t	ft_strlen_ms(const char *s);
size_t	ft_strlcpy_ms(char *dst, const char *src, size_t size);
char	*ft_getenv(t_ms *ms, char *str);
int		ft_is_special_cmd(char *big, char *little);

/******************    TOKENIZER    ******************/
void		create_tokens(char *input, t_ms *ms);
t_token		*ft_lstnew_tk(t_ms *ms, char *content);
t_token		*ft_lstlast_tk(t_token *lst);
void		ft_lstadd_back_tk(t_token **lst, t_token *new);
char		*ft_strndup_tk(t_ms *ms);
char		*ft_strchr_set(char *set, int c);
void		exit_handler(t_ms *ms, int exit_code);
void		ft_lstclear_token(t_token **token);
size_t		is_val_opp(const char *str_ptr, const char *end_ptr);

/******************    EXPANSER    ******************/
char		*expanser(char *s, t_ms *ms);
// PARSING UTILS
char	*ft_extract_var(char *s, t_ms *ms);
void	ft_fill_exp(char **dest, t_exp exp);
char	*ft_clear_space(char *src, t_ms *ms);

/******************    TRANSLATOR    ******************/
char	*ft_translate(char *s, t_ms *ms);

/******************    PARSER    ******************/
void		parse_cmd(t_ms *ms);
// PARSING UTILS
void		*ft_free(char **data);
// FT_LIST_CMD
t_cmd		*ft_lst_new_cmd(t_ms *ms);
t_cmd		*ft_lstlast_cmd(t_cmd *lst);
void		ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new);
t_infile	*ft_new_infile(t_token *token, t_ms *ms);
t_outfile	*ft_new_outfile(t_token *token, t_ms *ms);

/******************    EXEC    ******************/
void		exec_init(t_ms *ms);
// EXEC UTILS
int			ft_cmd_count(t_ms *ms);
void		initialize_variables(t_ms *ms);
char		**parse_arg(t_cmd *cmd, t_ms *ms);
void		free_split(char **arr);
void		close_fd(t_ms *ms, int *fd);
void		close_all_fds(t_ms *ms);
void		exec_here_doc(t_ms *ms, char *limiter, int i);

/******************    BUILTIN    ******************/
int		solo_builtin(t_ms *ms);
void	exec_builtin(t_ms *ms, t_cmd *cmd);
int		is_builtin_cmd(char *cmd);
// ENVIRONNEMENT MANAGEMENT
size_t	ft_env_count(char **env);
int		ft_find_var(char *path, t_ms *ms);
char	**ft_duplicate_env(t_ms *ms, char **env);
// UTILS
void	ft_builtins_exit(t_ms *ms, t_var **env_var, int exit_code);
// CD
void	cd_command(t_ms *ms, t_cmd *cmd);
// PWD
void	pwd_command(t_ms *ms, t_cmd *cmd);
// ENV
void	env_command(t_ms *ms);
// EXPORT
void	export_command(t_ms *ms, t_cmd *cmd);
t_var	**ft_get_variable(t_ms *ms, t_cmd *cmd);
int		ft_modify_env(t_var **env_var, t_ms *ms);
size_t	ft_find_var_count(t_cmd *cmd);
int		ft_is_all_alnum(char *str);
t_var	*ft_create_new_var(t_ms *ms, t_var **env_var);
// UNSET
void	unset_command(t_ms *ms, t_cmd *cmd);
// ECHO
void	echo_command(t_ms *ms, t_cmd *cmd);


/******************    TESTER    ******************/
void 	print_token(t_token *list);
void 	print_split(char **split);
void 	print_cmd(t_cmd *list);
void	ft_print_res_export(t_var **env_var);


/******************    LEXICAL    ******************/
int			lexical_analysis(t_ms *ms);
void		here_doc(t_ms *ms, char *limiter);

#endif
