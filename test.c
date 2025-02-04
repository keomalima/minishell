#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main(void)
{
    char *input;

    while ((input = readline("prompt> ")) != NULL)
    {
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }

        if (strcmp(input, "new_line") == 0)
        {
            printf("\nMoving to a new line...\n");
            rl_on_new_line(); // Inform Readline that the cursor is on a new line
            rl_replace_line("", 0); // Clear the current input line
            rl_redisplay(); // Redisplay the prompt
        }
        else
        {
            printf("You entered: %s\n", input);
        }

        add_history(input);
        free(input);
    }

    return 0;
}