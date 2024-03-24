#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
    static t_data data;

    (void)argc;
    (void)argv;
    data.envp = envp;

    while (1)
    {
        char *input = readline(YEL "Minishell > " RESET);
        parse(input, &data);
        //init enviromental variables
        pipe_it(&data);
        free(input);
    }
    return (0);
}
