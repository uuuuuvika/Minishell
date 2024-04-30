#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{

    (void)argc;
    (void)argv;

    while (1)
    {
        t_data *data = malloc(sizeof(t_data));
        //add error handling
        data->envp = envp;
        data->exit_code = 0;
        data->num_of_children = 0;
        data->sub = NULL;
        data->commands = malloc(10 * sizeof(t_cmd));//replace 10 with a macro
        char *input = readline(YEL "Minishell > " RESET);
        parse(input, data);
        // validate_cmds();
        // if (data->num_of_children == 1)
        // {
        //     printf(YEL "Executing simple cmd in main\n" RESET);
        //     exec_cmd(data, data->commands);
        // }
        // else
        pipe_cmds(data);
        free_data(data, input);
    }
    return (0);
}
