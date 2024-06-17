#include "minishell.h"

void write_error(const char *msg)
{
    write(2, msg, ft_strlen(msg)); // 2 is the file descriptor for stderr
}