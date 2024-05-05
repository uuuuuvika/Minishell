#include "minishell.h"

void ch_env_pwd(t_data *data, char *new_pwd, char *old_pwd)
{
    int i;

    i = 0;
    while (data->envs[i] != NULL)
    {
        if (ft_strncmp(data->envs[i], "PWD=", 4) == 0)
        {
            free(data->envs[i]);
            data->envs[i] = ft_strjoin("PWD=", new_pwd); 
        }
        else if (ft_strncmp(data->envs[i], "OLDPWD=", 7) == 0)
        {
            free(data->envs[i]);
            data->envs[i] = ft_strjoin("OLDPWD=", old_pwd);
        }
        i++;
    }
}

void ft_cd(t_data *data, t_cmd *cmd)
{
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    if (old_pwd == NULL)
    {
        perror("Failed to get current directory");
        return;
    }
    if (cmd->args[1] == NULL)
        return;
    printf(BLU "Directory before cd: " RESET);
    ft_pwd(data);
    if (chdir(cmd->args[1]) != 0)
    {
        perror("chdir failed");
		data->exit_code = 1;
        free(old_pwd);
        return;
    }
    new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL)
    {
        perror("Failed to get current directory");
        free(old_pwd);
        return;
    }
    printf(GRN "Directory after cd: " RESET);
    ft_pwd(data);
    ch_env_pwd(data, new_pwd, old_pwd);
    free(new_pwd);
    free(old_pwd);
}
