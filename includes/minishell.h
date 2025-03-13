/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:48:40 by lthan             #+#    #+#             */
/*   Updated: 2025/03/13 11:39:42 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <signal.h>

# ifndef ARG_MAX
#  define ARG_MAX 2097152
# endif

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
	int		in_file_err;
	int		out_file_err;
	char	**env;
	char	**cmd;
	int		pipe_fd[2][2];
	int		fd_in;
	int		fd_out;
	int		pipe_hd[2];
	int		here_doc_quit;
	pid_t	*child_pids;
}				t_exec;

typedef struct s_ms
{
	struct s_lexer	lexer;
	struct s_token	*token;
	struct s_cmd	*cmd;
	struct s_exec	*exec;
	int				exit_status;
	char			*input_main;
	char			**env;
	char			*lex_err;
	int				saved_out;
	int				saved_in;
}				t_ms;

typedef struct s_expand
{
	t_list	*initial_list;
	t_list	*exp_list;
	t_ms	*ms;
}				t_expand;

typedef struct s_exp_utils
{
	t_list	*new_list;
	char	*clean_quote;
}				t_ex_u;

/******************    UTILS    ******************/
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_getenv(t_ms *ms, char *str);
int			ft_isquote(char c);
int			ft_is_only_space(char *s);
void		ft_print_error(char *s1, char *s2, char *s3);
int			handle_key(char *rl);
void		sigint_handler(int sig);

/******************    CLEANER    ******************/
void		clean_ms(t_ms *ms, int exit_code);
void		exit_handler(t_ms *ms, int exit_code);
void		clean_t_cmd(t_cmd *cmd);

/******************    TOKENIZER    ******************/
void		create_tokens(char *input, t_ms *ms);
t_token		*ft_lstnew_tk(t_ms *ms, char *content);
t_token		*ft_lstlast_tk(t_token *lst);
void		ft_lstadd_back_tk(t_token **lst, t_token *new);
char		*ft_strchr_set(char *set, int c);
size_t		is_val_opp(const char *str_ptr, const char *end_ptr);
void		ft_lstdel_last_tk(t_token **lst);

/******************    EXPANSER    ******************/
void		ft_set_expanded_list(t_expand *expand, int hd);
void		ft_clear_expand(t_expand *expand, int exit_code);
void		ft_expand_alloc_failure(t_expand *expand, t_ex_u *util, char *str);
void		ft_skip_quote(char *s, int *i);
char		*ft_split_expand(char *s, int *j, t_expand *expand);
size_t		ft_count_exp(char *s);
size_t		ft_count_alpha_exp(char *s);
int			ft_check_for_space(char *s);
char		*ft_joined_list(t_ex_u *util, t_expand *expand);
char		*ft_joined_space_list(t_list *list, t_expand *expand);
char		*ft_handle_quote(char *s, t_expand *expand);
// REMPLACE EXPAND
t_list		*ft_remp_expand(char *str, t_expand *expand,
				char quote, t_ex_u *util);
char		*exp_exit_code(char *str, t_expand *expand, t_ex_u *util);
char		*exp_uid(char *str, t_expand *expand, t_ex_u *util);
char		*exp_digit_variable(char *str, t_expand *expand, t_ex_u *util);
char		*exp_quote_variable(char *str, t_expand *expand, t_ex_u *util);
char		*exp_valid_variable(char *s, t_expand *expand, t_ex_u *util);
char		*clear_string_space(char *s, t_expand *expand);

/******************    TRANSLATOR    ******************/
char		*ft_translate(char *s, t_ms *ms, int hd);
char		*ft_joined_final_list(t_expand *expand, int hd);

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
char		*ft_join_path(const char *s1, const char *s2);
void		error_handler(t_ms *ms, char **cmd, char *path);
int			is_valid_string(const char *str);

/******************    EXEC    ******************/
void		exec_init(t_ms *ms);
int			ft_cmd_count(t_ms *ms);
void		initialize_variables(t_ms *ms);
char		**parse_arg(t_cmd *cmd, t_ms *ms);
void		free_split(char **arr);
void		close_fd(t_ms *ms, int *fd);
void		close_all_fds(t_ms *ms);
int			file_handler(t_ms *ms, t_cmd *cmd);
void		switch_io_n_execve(t_cmd *cmd, t_ms *ms, int i);
int			solo_file_handler(t_cmd *cmd, t_ms *ms);
int			solo_exec_here_doc(t_ms *ms, char *limiter);
int			init_here_doc(t_ms *ms, char *limiter);
int			ft_strcmp_here_doc(const char *s1, const char *s2);
int			check_interupt(void);
void		sigint_here_doc(int sig);
int			sigquit_handler(t_ms *ms);
int			is_valid_string(const char *str);
void		handle_signals(t_ms *ms, int status, int sigint_handled);
void		handle_hd_fds(t_ms *ms);
void		handle_solo_builtins_exec(t_ms *ms, t_cmd *current);
void		close_exec_fds(t_ms *ms, int i);

/******************    BUILTIN    ******************/
void		exec_builtin(t_ms *ms, t_cmd *cmd);
int			is_builtin_cmd(char *cmd);
int			is_builtin_solo_cmd(t_ms *ms, char *cmd);
// ENVIRONNEMENT MANAGEMENT
size_t		ft_env_count(char **env);
int			ft_find_var(char *name, t_ms *ms);
char		**ft_duplicate_env(char **env);
// UTILS
void		ft_builtins_exit(t_ms *ms, t_var **env_var, int exit_code);
// CD
void		ft_update_pwd(t_ms *ms, char *path);
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

/******************    LEXICAL    ******************/
int			lexical_analysis(t_ms *ms);
void		here_doc(t_ms *ms, char *limiter);
int			is_valid_operand(t_token *token);
size_t		is_redir(const char *content);
int			ft_print_syntax_error(char *s);

#endif
