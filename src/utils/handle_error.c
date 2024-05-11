#include "minishell.h"

int handle_error(const char *message)
{
    perror(message);
    return (EXIT_FAILURE);
}