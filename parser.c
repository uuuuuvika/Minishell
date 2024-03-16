
int pars_input(char *input)
{
    char *line = strdup(input);
    char **token_array;

    token_array = split(line, " \t\n\r");
    printf("token_array[0]: %s\n", token_array[0]);

   
    return 0;
}