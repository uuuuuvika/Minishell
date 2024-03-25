#include "minishell.h"

void ft_pwd(t_data *data)
{
    char cwd[MAXPATHLEN];
   // int read_e = data->commands[0].pipe_out;
    int write_e = data->commands[1].pipe_in;
    // printf("PIPE 1 read_e: %d\n", read_e);
    //printf("PIPE 2 write_e: %d\n", write_e);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (write_e != -1)
        {
            if (write(write_e, cwd, strlen(cwd)) == -1)
            {
                perror(RED "write error in pwd" RESET);
                exit(1);
            }
            printf(BLU "\nWritting in" RESET " write_end: %d\n", write_e);
        } 
        else
            printf( "%s\n", cwd);
        exit(0);
    }
    else
    {
        perror("getcwd error");
        exit(0);
    }
}