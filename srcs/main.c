#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
}


int main (int arc, char **arv)
{
	// char	*rl;

	(void)arc;
	(void)arv;
	// print_split(arv + 1);

	
	// rl = readline("Prompt > ");

	t_token	*token_list;
	token_list = NULL;
	ft_lstadd_back_ms(&token_list, create_new_token("<"));
	ft_lstadd_back_ms(&token_list, create_new_token("in"));
	ft_lstadd_back_ms(&token_list, create_new_token("cmd1"));
	ft_lstadd_back_ms(&token_list, create_new_token("|"));
	ft_lstadd_back_ms(&token_list, create_new_token("cmd2"));
	ft_lstadd_back_ms(&token_list, create_new_token("$arg1"));
	ft_lstadd_back_ms(&token_list, create_new_token("arg2"));
	ft_lstadd_back_ms(&token_list, create_new_token("arg3"));
	ft_lstadd_back_ms(&token_list, create_new_token(">"));
	ft_lstadd_back_ms(&token_list, create_new_token("out"));
	ft_lstadd_back_ms(&token_list, create_new_token("|"));
	ft_lstadd_back_ms(&token_list, create_new_token("cmd3"));
	ft_lstadd_back_ms(&token_list, create_new_token("arg0"));
	ft_lstadd_back_ms(&token_list, create_new_token("arg1"));
	ft_lstadd_back_ms(&token_list, create_new_token(">>"));
	ft_lstadd_back_ms(&token_list, create_new_token("append"));
	ft_lstadd_back_ms(&token_list, create_new_token("|"));
	ft_lstadd_back_ms(&token_list, create_new_token("cmd4"));
	ft_lstadd_back_ms(&token_list, create_new_token("arg"));

	print_list(token_list);


	t_cmd	*cmd_list;

	cmd_list = NULL;
	parse_cmd(&cmd_list, token_list);


	// parse_lex(&token_list, split);

    // char *input;
	// char *str = "new content";

    // while ((input = readline("prompt > ")) != NULL)
	// {
	// 	rl_replace_line(str, 0);
	// 	rl_redisplay();
	// 	add_history(input);
	// 	free(input);
	// }
    return (0);
}
