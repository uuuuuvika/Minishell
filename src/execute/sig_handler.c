#include "minishell.h"
    
void sig_handler(int sig) {
  // Check if the signal is SIGINT (Ctrl+C)
  if (sig == SIGINT) {
    // Print a newline to maintain prompt formatting
    printf("\n");
	printf(YEL "Minishell > " RESET);
  }
}