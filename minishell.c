#include "minishell.h"
// TODO: add libft
// TODO: builtins
// TODO: parse input
// TODO: execute

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
        exec_cmd(&data, &data.commands[0]);
        if (ft_strcmp(input, "echo") == 0)
        {
            ft_echo("-n", data.envp);
            printf("NEW LINE?\n");
            //ft_pwd();
          //  break;
        }
        //free(input);
    }
    return (0);
}
