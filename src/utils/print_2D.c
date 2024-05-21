#include "minishell.h"

void print_2D(char **args)
{
	int j = 0;
	while(args[j])
	{
		printf(BLU "args[%d]: %s\n" RESET, j, args[j]);
		j++;
	}
}
