#include "minishell.h"

//old pipe function

// int pipe_it(t_data *data)
// {
//     pid_t pid;
//     int i = 0;

//     t_cmd **commands;
//     commands = malloc(5 * sizeof(t_cmd *));
//     commands[0] = data->commands;
//     commands[1] = data->commands->next;
//     // commands[2] = *data->commands[2].args;
//     // printf("Command 0: " BLU " %s " RESET, commands[0]);
//     // printf("Command 1: " BLU "%s\n" RESET, commands[1]);
//     int read_e = data->commands[0].pipe_out;
//     int write_e = data->commands[1].pipe_in;
//     printf("PIPE 1: %d\n", read_e);
//     printf("PIPE 2: %d\n", write_e);

//     // int pipe[2];
//     // pipe[PIPE_READ] = read_e;
//     // pipe[PIPE_WRITE] = write_e;
//     printf("Num of children in struct: " BLU "%d\n" RESET, data->num_of_children);
//     while (i < data->num_of_children)
//     {
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork error");
//             exit (1);
//         }
//         if (pid == 0)
//         {   
//             printf("ENTERS LOOP %d\n", i);
//             if (i == 0 && data->num_of_children > 1)
//             {
//            //     printf("LOOP 1" BLU " %s \n" RESET, commands[i]);
//                 close(read_e);
//                 // // PROTOTYPE: int dup2(int newfd, int oldfd);
//                 dup2(write_e, STDOUT);
//                 close(write_e);
//                 exec_cmd(data, commands[0]);
//             }
//             else if (i == 1 && data->num_of_children > 1)
//             {
//              //   printf("LOOP 2 %s\n " RESET , commands[i]);
//                 close(write_e);
//                 // // PROTOTYPE: int dup2(int newfd, int oldfd);
//                 dup2(read_e, STDIN);
//                 close(read_e);
//                 exec_cmd(data, commands[1]);
//             }
//         }
//         else
//         {
//             printf(YEL "Child PID " RESET "%d\n", pid);
//             printf(YEL "Parent PID %d " RESET "waiting...\n", getpid());
//             close(write_e);
//         }
//         i++;
//     }
//     wait(NULL);
//     close (write_e);
//     close (read_e);
//     return 0;
// }




//parser back-up
//printf("num_of_children: %d\n", data->num_of_children);

    // t_cmd *current = data->commands;
    // t_cmd *previous = NULL;
    // while (current)
    // {
    //     if (previous)
    //     {
    //         int p[2];
    //         pipe(p);
    //         previous->pipe_out = p[PIPE_WRITE];
    //         current->pipe_in = p[PIPE_READ];
    //     }
    //     previous = current;
    //     current = current->next;
    // }

    // t_cmd *current = data->commands;
    // // t_cmd *previous = NULL;
    // while (current)
    // {
    //     printf("num_args: %d\n", current->num_args);
    //     printf("cmd: %s\n", current->args[0]);
    //     printf("redirect_in: %d\n", current->redirect_in);
    //     printf("redirect_out: %d\n", current->redirect_out);
    //     printf("pipe_in: %d\n", current->pipe_in);
    //     printf("pipe_out: %d\n", current->pipe_out);
    //     //previous = current;
    //     current = current->next;
    // }






// int main(int argc, char *argv[], char **envp) //main with allocated memory for data
// {

//     (void)argc;
//     (void)argv;

//     while (1)
//     {
//         t_data *data = malloc(sizeof(t_data));
//         //add error handling
//         data->envp = envp;
//         data->exit_code = 0;
//         data->num_of_children = 0;
//         data->sub = NULL;
//         data->commands = malloc(10 * sizeof(t_cmd));//replace 10 with a macro
//         char *input = readline(YEL "Minishell > " RESET);
//         parse(input, data);
//         // validate_cmds();
//         // if (data->num_of_children == 1)
//         // {
//         //     printf(YEL "Executing simple cmd in main\n" RESET);
//         //     exec_cmd(data, data->commands);
//         // }
//         // else
//         pipe_cmds(data);
//         free_data(data, input);
//     }
//     return (0);
// }

 extern char **environ;

// tree structure 
// typedef enum CommandType
// {
//     CMD_SIMPLE,
//     CMD_PIPE,
//     CMD_REDIRECT
// } CommandType;

// typedef struct Command
// {
//     CommandType type;
//     // it means that the union can only hold one of the members at a time
//     union
//     {
//         struct
//         {
//             char *cmd;      // Command string
//             char *flags;    // Flags maybe?
//             char **args;    // Array of arguments
//             int num_args;   // Number of arguments
//         } simple;

//         struct
//         {
//             struct Command *left; // Left side of pipe 
//             struct Command *right; // Right side of pipe
//         } pipe;

//         struct
//         {
//             struct Command *cmd; // Command to be redirected
//             int input;
//             int output;
//         } redirect;
//     } data;
// } Command;

//parse the input (very basic)
int parse_input(char *input)
{
    char *line_copy;
    char *token;

    if (input == NULL)
    {
        printf("Error! Input is NULL.\n");
        return -1;
    }

    line_copy = strdup(input);

    if (line_copy == NULL)
    {
        printf("Error!\n");
        return -1;
    }

    token = strtok(line_copy, " \t\n\r");

    while (token != NULL)
    {
        printf("%s\n", token);

        if (is_builtin(token))
        {
            printf(RED "Found a builtin command --> %s\n" RESET, token);
            if (strcmp(token, "exit") == 0)
            {
                printf("Exiting minishell...\n");
                exit(0);
            }
            //uses forbiden global variable, oops
            if (strcmp(token, "env") == 0)
            {
                printf("Printing environment variables...\n");
                for (char **current = environ; *current; current++)
                {
                    puts(*current);
                }
                return 0;
            }
        }

        if (strcmp(token, "|") == 0)
            printf(RED "Found a pipe!\n" RESET);

        token = strtok(NULL, " \t\n\r");
    }

    free(line_copy);
    return 0;
}

//Hanneses forks and pipes
// int main()
// {
//     pid_t pid;
//     int i = 0;
//     char *paths[] = {"/bin/ls", "/bin/cat"};
//     char *cmd_1[] = {"ls", NULL};
//     char *cmd_2[] = {"cat", NULL};
//     char ***commands;

//     int pipes[2];
//     pipe(pipes);

//     printf("pipe[0]: %d\n", pipes[0]);
//     printf("pipe[1]: %d\n", pipes[1]);

//     commands = malloc(2 * sizeof(char **));
//     commands[0] = cmd_1;
//     commands[1] = cmd_2;
//     // while (1)
//     // {
//        // char *input = readline(YEL "Minishell > " RESET);

//         while (i < 2)
//         {
//             pid = fork();

//             if (pid == -1)
//             {
//                 perror("fork error");
//                 return (1);
//             }
//             if (pid == 0)
//             {
//                 // if (strcmp(input, "ls") == 0)
//                 // {
//                 if(i == 0)
//                 {
//                     //close it bc we dont use it, bc we dont need to read from it (just write)
//                     //writing end is 1
//                     //reading end is 0
//                     close(pipes[0]);

//                     dup2(pipes[1], 1);
//                     close(pipes[1]);
//                 }
//                 if(i == 1)
//                 {
//                     close(pipes[1]);
//                     dup2(pipes[0], 0);
//                     close(pipes[0]);
//                 }
//                 if (execve(paths[i], commands[i], NULL) == -1)
//                 {
//                     perror("execve");
//                     exit(1);
//                 }
//                 //}
//             }
//             // else
//             // {
//             //     wait(NULL);
//             // }
//             i++;
//             //close(pipes[1]);
//         }
//     wait(NULL);
//     //waitpid;
//         //free(input);
//     //}

//     close(pipes[0]);
//     close(pipes[1]);
//     return 0;
// }

// fgets(input, sizeof(input), stdin);
// input[strcspn(input, "\n")] = '\0';


// beta sub-shell
// void replace_for_expansion(char **args, char *cmd, t_data *data)
// {
// 	free(*args);
// 	if (is_multi_words(cmd))
// 	{
// 		// char **split = ft_split(cmd, ' ');
// 		// printf("split[0]: %s\n", split[0]);
// 		// printf("split[1]: %s\n", split[1]);
// 		int fd[2];
// 		pipe(fd);
// 		pid_t pid;
// 		char readbuffer[1000];
// 		if ((pid = fork()) < 0)
// 		{
// 			printf("Fork error: %s\n", strerror(errno));
// 		}
// 		else if (pid == 0)
// 		{ // Child process
// 			char **argv = ft_split(cmd, ' ');
// 			close(fd[0]);
// 			dup2(fd[1], 1); // You connect to the pipe in input mode
// 			char *path = find_path(argv[0], data);
// 			execve(path, argv, data->envs);
// 			close(fd[1]);
// 			printf("Shouldn't execute this\n");
// 			exit(1);
// 		}
// 		else
// 		{ // Father process
// 			wait(NULL);
// 			read(fd[0], readbuffer, sizeof(readbuffer));
// 			printf("Received string: %s", readbuffer);
// 			*args = ft_strdup(readbuffer);
// 			close(fd[0]);
// 			close(fd[1]);
// 		};
		
// 	}
// 	else
// 		*args = ft_strdup(cmd);
// }