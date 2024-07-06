#include "minishell.h"

char *add_space_to_redirect(char *line)
{
    char *new_line;
    int i;
    int j;

    new_line = malloc(sizeof(char) * (ft_strlen(line) * 2 + 1));
    i = 0;
    j = 0;
    while (line[i])
    {
        if (line[i] == '>' || line[i] == '<')
        {
            if (line[i + 1] == '>' || line[i + 1] == '<')
            {
                new_line[j++] = ' ';
                new_line[j++] = line[i++];
                new_line[j++] = line[i++];
                new_line[j++] = ' ';
            }
            else if (i != 0 && line[i - 1] != ' ' && line[i - 1] != '>' && line[i - 1] != '<')
            {
                new_line[j++] = ' ';
                new_line[j++] = line[i++];
                new_line[j++] = ' ';
            }
            else if (line[i + 1] != '\0' && line[i + 1] != ' ' && line[i + 1] != '>' && line[i + 1] != '<')
            {
                new_line[j++] = line[i++];
                new_line[j++] = ' ';
            }
        }
        else
            new_line[j++] = line[i++];
    }
    new_line[j] = '\0';
    return (new_line);
}