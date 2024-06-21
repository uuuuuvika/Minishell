#include "minishell.h"

char *split_expand_join(char *line, t_data *data)
{
    char *exp_line;
    char **splitted;
    int i;

    exp_line = ft_strdup("");
    splitted = ft_split(line, ' ');
    i = 0;

    // printf(BLU "line to expand: %s\n" RESET, line);
    // print_2D(splitted);
    // printf(BLU "num_args: %d\n" RESET, cnt_args(splitted));
    while (splitted[i])
    {
        // printf(BLU "Splitted[%d]: %s\n" RESET, i, splitted[i]);
        expand_arg(splitted, data);
        // printf(BLU "Expanded[%d]: %s\n" RESET, i, splitted[i]);
        //  if(ft_strchr(splitted[i], '$'))//Make it work for all expansions
        //  	splitted[i] = getenv(splitted[i] + 1);
        if (i > 0)
            exp_line = ft_strjoin(exp_line, " ");
        exp_line = ft_strjoin(exp_line, splitted[i]);
        i++;
    }
    // printf(GRN "expanded line: %s\n" RESET, exp_line);
    return (exp_line);
}

void hd_is_expansion_needed(t_cmd *new_node)
{
    int i = 0;
    while (new_node->args[i])
    {
        if (ft_strcmp(new_node->args[i], "<<") == 0)
        {
            if (new_node->args[i + 1][0] == '\'' || new_node->args[i + 1][0] == '\"')
                new_node->here_doc_exp = 0;
            else
                new_node->here_doc_exp = 1;
        }
        i++;
    }
}
