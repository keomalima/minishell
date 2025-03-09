#ifndef MINISHELL_H
# define MINISHELL_H

# define RED		"\033[1;31m"
# define red		"\033[0;31m"
# define GREEN	"\033[1;32m"
# define green	"\033[0;32m"
# define YELLOW	"\033[1;33m"
# define yellow	"\033[0;33m"
# define BLUE	"\033[1;34m"
# define blue	"\033[0;34m"
# define PURPLE	"\033[1;35m"
# define purple	"\033[0;35m"
# define RESET   "\033[0m"

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>

extern int	g_signal;

typedef enum e_type
{
	START,
	CMD,
	EXP,
	OPP,
	SQ,
	DQ,
	END
}				t_type;

typedef enum e_redir
{
	UNDEFINED,
	OUT_TRUNC,
	OUT_APPEND,
	IN,
	PIPE
}				t_redir;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	t_type		state;
	const char	*str_start;
	const char	*str_ptr;
	int			d_quo_open;
	int			s_quo_open;
}				t_lexer;

typedef struct s_files
{
	char	*name;
	int		is_lim;
	t_redir	type;
}				t_files;

typedef struct s_cmd
{
	char				**cmd;
	size_t				cmd_size;
	struct s_files		**files;
	size_t				files_size;
	t_redir				redir;
	struct s_cmd		*next;
	size_t				nb_expand;
}				t_cmd;

typedef struct s_index
{
	size_t	cmd_i;
	size_t	file_i;
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

typedef struct s_ms
{
	struct s_lexer	lexer;
	struct s_token	*token;
	struct s_cmd	*cmd;
	struct s_exec	*exec;
	int				exit_status;
	char			**env;
	char			*lex_err;
	int				saved_out;
	int				saved_in;
}				t_ms;

typedef struct s_expans
{
	t_list	*initial_list;
	t_list	*exp_list;
	t_ms	*ms;
}				t_expand;

/******************    UTILS    ******************/
int			ft_strcmp(const char *s1, const char *s2);
void		clean_ms(t_ms *ms, int exit_code);
char		*ft_getenv(t_ms *ms, char *str);
int			ft_is_special_cmd(char *big, char *little);
int			ft_isquote(char c);
void		initialize_var(t_ms *ms);
int			handle_key(char *rl);
void		sigint_handler(int sig);
// void	del_content(void *content);
void		ft_print_error(char *s1, char *s2, char *s3);
int			ft_is_only_space(char *s);

/******************    TOKENIZER    ******************/
void		create_tokens(char *input, t_ms *ms);
t_token		*ft_lstnew_tk(t_ms *ms, char *content);
t_token		*ft_lstlast_tk(t_token *lst);
void		ft_lstadd_back_tk(t_token **lst, t_token *new);
char		*ft_strchr_set(char *set, int c);
void		exit_handler(t_ms *ms, int exit_code);
size_t		is_val_opp(const char *str_ptr, const char *end_ptr);

/******************    EXPANSER    ******************/
void		ft_set_expanded_list(t_expand *expand);
t_list		*ft_remplace_by_expand(char *str, t_expand *expand, char quote);
char		*exp_exit_code(t_expand *expand);
char		*exp_uid(t_expand *expand);
char		*exp_digit_variable(char *s, t_expand *expand);
char		*exp_quote_variable(char *s, t_expand *expand);
char		*exp_valid_variable(char *s, t_expand *expand);

char		*clear_string_space(char *s, t_expand *expand);
void		ft_clear_expand(t_expand *expand, int exit_code);
void		ft_skip_quote(char *s, int *i);
char		*ft_split_expand(char *s, int *j, t_expand *expand);
size_t		ft_count_exp(char *s);
size_t		ft_count_alpha_exp(char *s);
int			ft_check_for_space(char *s);

/******************    TRANSLATOR    ******************/
char		*ft_translate_file(char *s, t_ms *ms);
char		*ft_translate_heredoc(char *s, t_ms *ms);
char		*ft_joined_list(t_list *list, t_expand *expand);
char		*ft_joined_final_list(t_expand *expand);
char		*ft_reset_outside_quote(char *ret, char *s, t_ms *ms);

/******************    PARSER    ******************/
void		parse_cmd(t_ms *ms);
// PARSING UTILS
void		*ft_free(char **data);
// FT_LIST_CMD
t_cmd		*ft_lst_new_cmd(t_ms *ms);
t_cmd		*ft_lstlast_cmd(t_cmd *lst);
void		ft_lstadd_back_cmd(t_cmd **cmd_list, t_cmd *new);
size_t		is_opp_file(const char *s1);
t_files		*ft_new_file(t_token *token, t_ms *ms, t_cmd *cmd);
void		ft_find_cmd_size(t_token *token, t_cmd *new);
void		ft_initialize_index(t_index *index);
void		clean_new_cmd(t_ms *ms, t_cmd *new);

/******************    EXEC    ******************/
void		exec_init(t_ms *ms);
// EXEC UTILS
int			ft_cmd_count(t_ms *ms);
void		initialize_variables(t_ms *ms);
char		**parse_arg(t_cmd *cmd, t_ms *ms);
void		free_split(char **arr);
void		close_fd(t_ms *ms, int *fd);
void		close_all_fds(t_ms *ms);
void		file_handler(t_cmd *cmd, t_ms *ms, int i);
void		switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i);
int			solo_file_handler(t_cmd *cmd, t_ms *ms);
int			solo_exec_here_doc(t_ms *ms, char *limiter);
void		init_here_doc(t_ms *ms, t_cmd *cmd, int i);
int			ft_strcmp_here_doc(const char *s1, const char *s2);
int			check_interupt(void);
void		sigint_here_doc(int sig);
void		sigquit_handler(void);
int			is_valid_string(const char *str);

/******************    BUILTIN    ******************/
void		exec_builtin(t_ms *ms, t_cmd *cmd);
int			is_builtin_cmd(char *cmd);
int			is_builtin_solo_cmd(t_ms *ms, char *cmd);
// ENVIRONNEMENT MANAGEMENT
size_t		ft_env_count(char **env);
int			ft_find_var(char *name, t_ms *ms);
char		**ft_duplicate_env(t_ms *ms, char **env);
// UTILS
void		ft_builtins_exit(t_ms *ms, t_var **env_var, int exit_code);
// CD
void		ft_update_pwd(t_ms *ms);
int			ft_check_valid_dir(t_ms *ms, t_cmd *cmd, char **path);
void		cd_command(t_ms *ms, t_cmd *cmd);
// PWD
void		pwd_command(t_ms *ms);
// ENV
void		env_command(t_ms *ms, t_cmd *cmd);
// EXPORT
void		export_command(t_ms *ms, t_cmd *cmd);
t_var		**ft_get_variable(t_ms *ms, t_cmd *cmd);
int			ft_modify_env(t_var **env_var, t_ms *ms, t_cmd *cmd);
size_t		ft_find_var_count(t_cmd *cmd);
int			ft_is_all_alnum(char *str);
t_var		*ft_create_new_var(t_ms *ms, t_var **env_var);
size_t		ft_count_arg(char **cmd);
// UNSET
void		unset_command(t_ms *ms, t_cmd *cmd);
// ECHO
void		echo_command(t_ms *ms, t_cmd *cmd);
// EXIT
void		exit_command(t_ms *ms, t_cmd *cmd);

/******************    TESTER    ******************/
void		print_token(t_token *list);
void		print_split(char **split);
void		print_cmd(t_cmd *list);
void		ft_print_res_export(t_var **env_var);

/******************    LEXICAL    ******************/
int			lexical_analysis(t_ms *ms);
void		here_doc(t_ms *ms, char *limiter);
int			is_valid_operand(t_token *token);
size_t		is_redir(const char *content);
int			ft_print_syntax_error(char *s);

#endif
