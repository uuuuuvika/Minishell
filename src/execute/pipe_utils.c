#include "minishell.h"

void	fd_close(t_cmd *current)
{
	if (current->pipe_in != -1)
		close(current->pipe_in);
	if (current->pipe_out != -1)
		close(current->pipe_out);
	if (current->redirect_in != -1)
		close(current->redirect_in);
	if (current->redirect_out != -1)
		close(current->redirect_out);
	if (current->here_doc != 0)
		close(current->here_doc);
}

void	ultimate_fd_close(t_data *data)
{
	t_cmd	*current;

	current = data->commands;
	while (current != NULL)
	{
		fd_close(current);
		current = current->next;
	}
}

void	ultimate_wait(t_data *data, pid_t *pid)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < data->num_of_children)
	{
		if (waitpid(pid[i], &exit_code, 0) == -1)
			handle_error("waitpid failed");
		if (WIFEXITED(exit_code))
			data->exit_code = WEXITSTATUS(exit_code);
		i++;
	}
}

void	fd_dup2(t_cmd *current)
{
	if (current->here_doc != 0)
	{
		int r = open(BLU"here_doc"RESET, O_RDONLY, 777);
		printf(BLU "here_doc: %d\n" RESET, r);//////////
		if (dup2(r, STDIN) == -1)
			handle_error("dup2 error here_doc");
	}
	if (current->pipe_in != -1)
	{
		if (dup2(current->pipe_in, STDIN) == -1)
			handle_error("dup2 error pipe_in");
	}
	else if (current->redirect_in != -1)
	{
		if (dup2(current->redirect_in, STDIN) == -1)
			handle_error("dup2 error redirect_in");
	}
	if (current->redirect_out != -1)
	{
		if (dup2(current->redirect_out, STDOUT) == -1)
			handle_error("dup2 error redirect_out");
	}
	else if (current->pipe_out != -1)
	{
		if (dup2(current->pipe_out, STDOUT) == -1)
			handle_error("dup2 error pipe_out");
	}
	
}