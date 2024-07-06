#include "minishell.h"

void expand_dsqm(char **arg, t_data *data)
{
	int i = 0;
    int j = 0;
    int count = 0;
    char *result;
    char *tmp;

	if (g_signal == 2)
	{
		data->exit_code = 130;
		g_signal = 0;
	}
	// char *tmp = ft_itoa(data->exit_code);
	// replace_for_expansion(arg, tmp);
	// free(tmp);
	count = count_dsqm(arg);
        if (count > 0)
        {
            result = ft_strdup("");
            while ((*arg)[i])
            {
                if ((*arg)[i] == '$' && (*arg)[i + 1] == '?')
                {
                    tmp = ft_substr(*arg, j, i - j);
                    result = ft_strjoin(result, tmp);
                    free(tmp);
                    tmp = ft_itoa(data->exit_code);
                    result = ft_strjoin(result, tmp);
                    free(tmp);
                    i += 2;
                    j = i;
                }
                else
                    i++;
            }
            tmp = ft_substr(*arg, j, i - j);
            result = ft_strjoin(result, tmp);
            free(tmp);
            free(*arg);
            *arg = result;
        }
}