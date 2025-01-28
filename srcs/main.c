#include "minishell.h"

void	initialize_var(t_ms *ms)
{
	ms->token = NULL;
}


int main (int arc, char **arv)
{
	char	*rl;

	(void)arc;
	(void)arv;
	// print_split(arv + 1);

	rl = readline("Prompt > ");

	get_var(rl);
	// printf("%s\n", arv[1], get_var(arv[1]));
	

	// t_ms	ms;

	// ms.token = NULL;
	// ft_lstadd_back_token(&ms.token, create_new_token("<"));
	// ft_lstadd_back_token(&ms.token, create_new_token("in"));
	// ft_lstadd_back_token(&ms.token, create_new_token("cmd1"));
	// ft_lstadd_back_token(&ms.token, create_new_token("|"));
	// ft_lstadd_back_token(&ms.token, create_new_token("cmd2"));
	// ft_lstadd_back_token(&ms.token, create_new_token("$arg1"));
	// ft_lstadd_back_token(&ms.token, create_new_token("arg2"));
	// ft_lstadd_back_token(&ms.token, create_new_token("arg3"));
	// ft_lstadd_back_token(&ms.token, create_new_token(">"));
	// ft_lstadd_back_token(&ms.token, create_new_token("outfile"));
	// ft_lstadd_back_token(&ms.token, create_new_token("|"));
	// ft_lstadd_back_token(&ms.token, create_new_token("cmd3"));
	// ft_lstadd_back_token(&ms.token, create_new_token("arg0"));
	// ft_lstadd_back_token(&ms.token, create_new_token("arg1"));
	// ft_lstadd_back_token(&ms.token, create_new_token("|"));
	// ft_lstadd_back_token(&ms.token, create_new_token("cmd4"));
	// ft_lstadd_back_token(&ms.token, create_new_token(">>"));
	// ft_lstadd_back_token(&ms.token, create_new_token("append"));
	// ft_lstadd_back_token(&ms.token, create_new_token("arg"));
	// print_token(ms.token);

	// ms.cmd = NULL;
	// parse_cmd(&ms);
	// print_cmd(ms.cmd);


	// parse_lex(&ms.token, split);

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
