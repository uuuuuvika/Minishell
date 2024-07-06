#include "minishell.h"

// int	is_redirect(char *str)
// {
// 	return (ft_strncmp(str, ">", 1) == 0
// 		|| ft_strncmp(str, "<", 1) == 0
// 		|| ft_strncmp(str, ">>", 2) == 0
// 		|| ft_strncmp(str, "<<", 2) == 0);
// }

//Dai, ur change (strncmp instead of strcmp) was bringing a bug, so I changed it back to strcmp
int is_redirect(char *str)
{
    return (ft_strcmp(str, ">") == 0 
    || ft_strcmp(str, "<") == 0 
    || ft_strcmp(str, ">>") == 0
    || ft_strcmp(str, "<<") == 0);
}

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

int redirect_assign(t_cmd *current, t_data *data)
{
    int i;

    i = 0;
    while (current->args[i])
    {
        if (ft_strcmp(current->args[i], ">") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (current->redirect_out == -1)
            {
                write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error(current->args[i + 1]);
                    write_error(": No such file or directory\n");
                    return (1);
                }
                write_error("syntax error near unexpected token `newline'\n");
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], "<") == 0)
        {
            current->redirect_in = open(current->args[i + 1], O_RDONLY);
            if (current->redirect_in == -1)
            {
                write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error(current->args[i + 1]);
                    write_error(": No such file or directory\n");
                    return (1);
                }
                write_error("syntax error near unexpected token `newline'\n");
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], ">>") == 0)
        {
            current->redirect_out = open(current->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (current->redirect_out == -1)
            {
                write_error("minishell: ");
                if (current->args[i + 1])
                {
                    write_error(current->args[i + 1]);
                    write_error(": No such file or directory\n");
                    return (1);
                }
                write_error("syntax error near unexpected token `newline'\n");
                return (2);
            }
            i++;
        }
        else if (ft_strcmp(current->args[i], "<<") == 0){
                read_heredoc(current->args[i + 1], current, data);
                //current->args[i][0] ='\0';
                //current->args[i + 1][0] = '\0';
                //current->args[i] = ft_strdup("here_doc");
                //current->args[i + 1] = '';
                i++;
        }
        i++;
    }
    return (0);
}


int handle_redirects(t_cmd *new_node, t_data *data, char **future_children)
{
    int j;

    j = redirect_assign(new_node, data);
    if (j != 0)
    {
        //printf("Error: %d\n", j);
        free_arr2D(new_node->args);
        free(new_node);
        free_arr2D(future_children);
        free_arr2D(data->sub);
        free_arr2D(data->subb);
        data->exit_code = j;
        return (1);
    }
    return (0);
}

void redirect_fd_dup(t_cmd *current, t_data *data)
{
    if (current->redirect_in != -1)
    {
        if (dup2(current->redirect_in, STDIN) == -1)
            handle_error("dup2 error redirect_in");
        close(current->redirect_in);
    }
    if (current->redirect_out != -1)
    {
        if (dup2(current->redirect_out, STDOUT) == -1)
            handle_error("dup2 error redirect_out");
        close(current->redirect_out);
    }
    if (data->cmn_here_doc != 0)
    {
        if (dup2(data->cmn_here_doc, STDOUT) == -1)
            handle_error("dup2 error here_doc");
        close(data->cmn_here_doc);
    }
}
