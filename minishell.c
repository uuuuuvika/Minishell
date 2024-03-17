#include "minishell.h"
// TODO: write our own strcmp
// TODO: add libft
// TODO: builtins
// TODO: parse input
// TODO: execute

int main(int argc, char *argv[], char **envp)

{
    t_data  data;

    (void)argc;
    (void)argv;
    data.envp = envp;

    // Print the environment variables (just for testing purposes, remove it later!)
    while(data.envp != NULL && *data.envp != NULL)
    {
        printf("%s\n", *data.envp);
        data.envp++;
    }

    while (1)
    {
        // DAI! Feel free to add other colors/emojis or rename it in any way you like!
        char *input = readline(YEL "Minishell > " RESET);

        printf(YEL "Minishell > " RESET);
        printf("yo! you entered: %s\n", input);
        free(input);
    }

    return (0);
}
