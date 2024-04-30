#include "minishell.h"

void ch_env_pwd(t_data *data, char *new_pwd, char *old_pwd)
{
    char **env_var;
    int i;

    env_var = data->envs->var;
    i = 0;
    char *new_env = ft_strjoin("PWD=", new_pwd);
    if (env_var == NULL) {
        printf(RED "env_var is null in ch_env_pwd()\n" RESET);
        exit(1);
    }
    while (env_var[i] != NULL)
    {
        if (ft_strncmp(env_var[i], "PWD=", 4) == 0)
            env_var[i] = ft_strdup(new_env);
        else if (ft_strncmp(env_var[i], "OLDPWD=", 7) == 0)
            env_var[i] = ft_strjoin("OLDPWD=", old_pwd);
        i++;
    }
    data->envs->var = env_var;
}

void ft_cd(t_data *data, t_cmd *cmd)
{
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    //old_pwd = getcwd(cwd, sizeof(cwd));
    if (old_pwd == NULL)
    {
        perror("Failed to get current directory");
        return;
    }
    if (cmd->args[1] == NULL)
        return;
    printf(BLU "Directory before cd: " RESET);
    //printf("%s\n", old_pwd);
	ft_pwd(data);
    //printf("%s\n", new_pwd);
    //ft_pwd(data);
    // printf(BLU "Enviroment PWD before: " RESET "%s\n", getenv("PWD"));
    //     ft_env(data);
    if (chdir(cmd->args[1]) != 0) {
        perror("chdir failed");
        free(old_pwd);
        return;
    }
    new_pwd = getcwd(NULL, 0); // Obtiene el nuevo directorio
    if (new_pwd == NULL) {
        perror("Failed to get current directory");
        free(old_pwd);
        return;
    }
    ch_env_pwd(data, new_pwd, old_pwd);
    printf(GRN "Directory after cd: " RESET);
    ft_pwd(data);

    // printf(GRN "Enviroment PWD after: " RESET "%s\n", getenv("PWD"));
    // ft_env(data);
    free(new_pwd);
    free(old_pwd);
}
