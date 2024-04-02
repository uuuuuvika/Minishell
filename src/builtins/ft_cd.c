#include "minishell.h"

void ch_env_pwd(t_data *data, char *new_path)
{
    char **envp;
    int i;

    envp = data->envp;
    i = 0;
    char *new_env = ft_strjoin("PWD=", new_path);
    char *old_env;
    old_env = getenv("PWD");
    if (envp == NULL) {
        printf(RED "envp is null\n" RESET);
        exit(1);
    }
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PWD=", 4) == 0)
            envp[i] = new_env;
        else if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
            envp[i] = ft_strjoin("OLDPWD=", old_env);
        i++;
    }
    printf(GRN "Enviroment PWD after: " RESET "%s\n", getenv("PWD"));
    printf(GRN "Enviroment OLDPWD after: " RESET "%s\n", getenv("OLDPWD"));
    data->envp = envp;
}

void ft_cd(t_data *data, t_cmd *cmd)
{
    if (cmd->args[1] == NULL)
        exit(0);
    printf(GRN "Directory before cd: " RESET);
    ft_pwd(data);
    printf(GRN "Enviroment PWD before: " RESET "%s\n", getenv("PWD"));
    if (chdir(cmd->args[1]) != 0)
        printf(RED "Can not change directory" RESET);
    ch_env_pwd(data, cmd->args[1]);
    printf(GRN "Directory after cd: " RESET);
    ft_pwd(data);
    printf(GRN "Enviroment PWD after: " RESET "%s\n", getenv("PWD"));
    ft_env(data);
}