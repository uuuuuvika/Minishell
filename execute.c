//

void exec_ls(char *str)
{
    char *args[] = {"ls", "-l", NULL}; // Argumentos para el comando ls
    char *envp[] = {NULL}; // Variables de entorno (en este caso, ninguna)
    if (strcmp(str, "ls") == 0)
    {
        if (execve("/bin/ls", args, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
  //  exit(0);
}