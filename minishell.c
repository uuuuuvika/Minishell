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
    static t_command *com;
    com = malloc(sizeof(t_command));
    com->args = malloc(sizeof(char *) * 3);
    com->args[0] = "date";
    com->args[1] = NULL;
    com->args[2] = NULL;
    char *input = readline(YEL "Minishell > " RESET);
  
        ///If cmd is not builtin we send it here:
            exec_cmd(&data, com); //exec_cmd(t_data *data, char **args)

        if (ft_strcmp(input, "echo") == 0)
        {
            ft_echo("-n", data.envp);
            printf("NEW LINE?\n");
            //ft_pwd();
          //  break;
        }
        // printf("yo! you entered: %s\n", input);
        free(input);

    return (0);
}
