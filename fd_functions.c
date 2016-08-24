#include <sh21.h>

void	close_fd(t_fd *fd)
{
	while (fd)
	{
		if (fd->fd > 2)
			close(fd->fd);
		fd = fd->next;
	}
}
void	close_fd_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		close_fd(cmd->fd_in);
		close_fd(cmd->fd_out);
		close_fd(cmd->fd_err);
		cmd = cmd->next;
	}
}

void print_fd(t_fd *list)
{
	while (list)
	{
		printf("[%d] ", list->fd);
		list = list->next;
	}
	printf("\n");
}

void print_fd_list(t_cmd *list)
{
	printf("fd_in : ");
	print_fd(list->fd_in);
	printf("fd_out : ");
	print_fd(list->fd_out);
	printf("fd_err : ");
	print_fd(list->fd_err);
	printf("\n");
}

t_fd	*create_fd(int fd, int fd_pointe)
{
	t_fd	*elem;

	elem = (t_fd*)malloc(sizeof(t_fd));
	elem->next = NULL;
	elem->fd = fd; //
	elem->fd_pointe = fd_pointe;
	return (elem);
}

t_fd 	*add_fd_elem(t_fd *list, t_fd *elem)
{
	t_fd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
  		list = list->next;
	list->next = elem;
	if (list->fd < 0)
	{
		free(list);
		return(elem);
	}
	return (tmp);
}

t_fd	*copy_fd(t_fd *list)
{
	t_fd *copy;

	copy = NULL;
	while (list)
	{
		copy = add_fd_elem(copy, create_fd(dup(list->fd), list->fd_pointe));
		list = list->next;
	}
	return (copy);
}
