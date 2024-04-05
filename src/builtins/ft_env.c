#include "minishell.h"

void ft_env(t_data *data)
{
    // char **envp;
    int i = 0;
    // envp = envs->var;
    if (data->envs->var == NULL)
    {
        printf(RED "envp is null\n" RESET);
        return;
    }
    while (data->envs->var[i] != NULL)
    { 
        printf("%s\n", data->envs->var[i]);
        i++;
    }
}


// void ft_env(t_data *data)
// {
//     char **envp;

//     envp = data->envp;
//     if (envp == NULL)
//     {
//         printf(RED "envp is null\n" RESET);
//         return;
//     }
//     while (*envp != NULL)
//     {
//         printf("%s\n", *envp);
//         envp++;
//     }
// }