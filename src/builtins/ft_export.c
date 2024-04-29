#include "minishell.h"

void ft_export(t_data *data, t_cmd *cmd)
{
    int     i;
    int     j;
    char    **new_var;

    i = 0;
    j = 1;
    check_NULL(cmd->args[1]); //neeed to check args format as well
    new_var = malloc(sizeof(char*) * (count_env(data->envs->var) + 2));
    if (new_var == NULL)
    {
        perror("Malloc failed");
        exit(1);
    }
    //if var is present then replace it
    // if (ft_strncmp( envar[i], cmd->args[j], ft_strlen(cmd->args[1])) == 0);
    //     return;
    while(cmd->args[j] != NULL)
    {
        while(data->envs->var[i] != NULL)
        {
            new_var[i] = ft_strdup(data->envs->var[i]);
            i++;
        }
        new_var[i] = ft_strdup(cmd->args[j]);
        i++;
        new_var[i] = NULL;
        j++;
    }
	free(data->envs->var);
	data->envs->var = new_var;
	i = 0;
	while(new_var[i])
	{
		data->envs->var[i] = ft_strdup(new_var[i]);
		i++;
	}
    //PRINT AFTER
    i = 0;
    while (data->envs->var[i] != NULL)
    { 
        printf(GRN "%s\n" RESET, data->envs->var[i]);
        i++;
    }
}


// void ft_export(t_data *data, t_cmd *cmd)
// {
//     int     i;
//     int     j;
//     char    **envar;
//     char    **new_var;

//     i = 0;
//     j = 1;
//     envar = data->envs->var;

//     check_NULL(cmd->args[1]); //neeed to check args format as well
//     new_var = malloc(sizeof(char*) * (count_env(envar) + 2));
//     if (new_var == NULL)
//     {
//         perror("Malloc failed");
//         exit(1);
//     }
//     //if var is present then replace it
//     // if (ft_strncmp( envar[i], cmd->args[j], ft_strlen(cmd->args[1])) == 0);
//     //     return;
//     while(cmd->args[j] != NULL)
//     {
//         while(envar[i] != NULL)
//         {
//             new_var[i] = ft_strdup(envar[i]);
//             i++;
//         }
//         new_var[i] = ft_strdup(cmd->args[j]);
//         i++;
//         new_var[i] = NULL;
//         j++;
//     }
// 	free(data->envs->var);
// 	data->envs->var = new_var;
// 	i = 0;
// 	while(new_var[i])
// 	{
// 		data->envs->var[i] = ft_strdup(new_var[i]);
// 		i++;
// 	}
//     //PRINT AFTER
//     i = 0;
//     while (data->envs->var[i] != NULL)
//     { 
//         printf(GRN "%s\n" RESET, data->envs->var[i]);
//         i++;
//     }
// }