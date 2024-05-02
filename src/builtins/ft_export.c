#include "minishell.h"

int varname_len(char *var)
{
    int i;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    return (i);
}

int var_cmp(char **envar, char *newvar)
{
    int i = 0;
    while (envar[i])
    {
        if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
            return (1);
        i++;
    }
    return (0);
}

int replace_var(char **envar, char *newvar)
{
    int i = 0;
    while (envar[i])
    {
        if ((varname_len(envar[i]) == varname_len(newvar)) && (ft_strncmp(envar[i], newvar, varname_len(envar[i])) == 0))
        {
            free(envar[i]);
            envar[i] = ft_strdup(newvar);
            return (1);
        }
        i++;
    }
    return (0);
}

int add_var(char ***envar, char *newvar)
{
    char **tmp = malloc(sizeof(char *) * (count_env(*envar) + 2));
    int i = 0;
    while ((*envar)[i])
    {
        tmp[i] = ft_strdup((*envar)[i]);
        i++;
    }
    tmp[count_env(*envar)] = ft_strdup(newvar);
    tmp[count_env(*envar) + 1] = NULL;
    free_arr2D(*envar);
    *envar = tmp;
    return 0;
}

void ft_export(t_data *data, t_cmd *cmd)
{
    int j;

    j = 1;
    // check_NULL(cmd->args[1]); // need to check args format as well
    while (cmd->args[j] != NULL)
    {
        if (var_cmp(data->envs, cmd->args[j]) == 1)
        {
            printf(YEL "Replace variable\n" RESET);
            replace_var(data->envs, cmd->args[j]);
        }
        else
        {
            printf(GRN "Add variable\n" RESET);
            add_var(&data->envs, cmd->args[j]);
        }
        j++;
    }
}
