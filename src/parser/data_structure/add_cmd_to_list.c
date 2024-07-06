#include "minishell.h"

void add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd *current;

	current = NULL;
	if (*cmd_list == NULL)
		*cmd_list = new_node;
	else
	{
		current = *cmd_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}