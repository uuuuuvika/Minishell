#include "minishell.h"

void ft_echo(t_data *data, char **args)
{
    (void) data;
    int i;
    
    i = 1;
    printf(GRN "Executing builtin echo\n" RESET);
    while (args[i])
    {
        if (ft_strcmp(args[i], "-n") == 0)
            i++;
        printf("%s", args[i]);
        i++;
    }
    if (ft_strcmp(args[1], "-n") != 0)
        printf("\n");
}

// void ft_echo(t_data *data, char **args)
// {
//     int i;
    
//     i = 1;
//     int write_e = data->commands[1].pipe_in;
//     printf(GRN "Executing builtin echo\n" RESET);
//     while (args[i])
//     {
//         if (ft_strcmp(args[i], "-n") == 0)
//             i++;
//         if (write_e != -1) //If file descriptor is passed, write strings
//         {
//             if (write(write_e, args[i], strlen(args[i])) == -1)
//             {
//                 perror(RED "write error in echo" RESET);
//                 exit(1);
//             }
//             printf(BLU "\nWritting in" RESET " write_end: %d\n", write_e);
//         }
//         else
//             printf("%s", args[i]);
//         i++;
//     }
//     if (ft_strcmp(args[1], "-n") != 0)
//         printf("\n");
// }
