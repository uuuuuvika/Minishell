#include "minishell.h"

void ch_env_pwd(t_data *data, char *new_path)
{
    char **envp;
    int i;
    
    envp= data->envp;
    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
        {
            envp[i] = ft_strjoin("PWD=", new_path);
        }
        else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
        {
            envp[i] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
        } 
        i++;
    }
    data->envp = envp;
}

void ft_cd(t_data *data, char *new_path)
{
    (void) data;
    printf(YEL "Directory before cd: " RESET);
    ft_pwd();
    printf(YEL"Enviroment PWD before: " RESET "%s\n", getenv("PWD"));
    //ft_env(*data);
    if (chdir(new_path) != 0)
        printf(RED "Can not change directory" RESET);
    ch_env_pwd(data, new_path);
    printf(GRN "Directory after cd: " RESET);
    ft_pwd();
    printf(GRN "Enviroment PWD after: " RESET "%s\n", getenv("PWD"));
    //ft_env(*data);
}