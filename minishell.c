#include "minishell.h"
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
        char *input = readline(YEL "Minishell > " RESET);
  
        ///If cmd is not builtin we send it here:
            char *args[] = {input, NULL, NULL};
            exec_cmd(&data, args); //exec_cmd(t_data *data, char **args)

        if (ft_strcmp(input, "echo") == 0)
        {
            ft_echo("-n", data.envp);
            printf("NEW LINE?\n");
            //ft_pwd();
            break;
        }
        // printf("yo! you entered: %s\n", input);
        free(input);
    }

    return (0);
}
