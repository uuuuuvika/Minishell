#include "minishell.h"
    
void sig_handler(int sig)
{
  if (sig == SIGINT)
  {
		printf("\n");
		printf(YEL "Minishell > " RESET);
  }
}