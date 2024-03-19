#include "minishell.h"
// TODO: write our own strcmp
// TODO: add libft
// TODO: builtins
// TODO: parse input
// TODO: execute

int main(int argc, char *argv[], char **envp)

{
    static t_data data;
    static t_command *commands;

    (void)argc;
    (void)argv;
    data.envp = envp;

    while (1)
    {
        // DAI! Feel free to add other colors/emojis or rename it in any way you like!
        char *input = readline(YEL "Minishell > " RESET);

        parse(input, &data);
        //printf("yo! you entered: %s\n", input);
        free(input);
    }

    return (0);
}
