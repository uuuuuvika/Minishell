#include "minishell.h"
// TODO: write our own strcmp
// TODO: add libft
// TODO: builtins
// TODO: parse input
// TODO: execute

int main(int argc, char *argv[], char **envp)

{
    t_data data;

    (void)argc;
    (void)argv;
    data.envp = envp;
    //char *arg[2] = { "potato", NULL };

    while (1)
    {
        // DAI! Feel free to add other colors/emojis or rename it in any way you like!
        char *input = readline(YEL "Minishell > " RESET);

        if (ft_strcmp(input, "echo") == 0)
        {
            ft_echo("n", data.envp);
            printf("NEW LINE?");
            //ft_pwd();
            break;
        }
        // printf("yo! you entered: %s\n", input);
        free(input);
    }

    return (0);
}
