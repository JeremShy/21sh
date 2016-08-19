#include <sh21.h>

void delete_list_fd(t_fd *list)
{
	t_fd *tmp;

	while(list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void delete_list_command(t_cmd *list)
{
	t_cmd *tmp;

	while(list)
	{
		tmp = list->next;
		free_char_tab(list->av);
		delete_list_fd(list->fd_in);
		delete_list_fd(list->fd_out);
		delete_list_fd(list->fd_err);
		free(list);
		list = tmp;
	}
}

void delete_list_history(t_history *list)
{
	t_history *tmp;

	while(list)
	{
		tmp = list->prec;
		free(list->line);
		free(list);
		list = tmp;
	}
}
