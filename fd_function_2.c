#include <sh21.h>

void		print_fd(t_fd *list)
{
	while (list)
	{
		printf("[%d] ", list->fd);
		list = list->next;
	}
	printf("\n");
}

void		print_fd_list(t_cmd *list)
{
	printf("fd_in : ");
	print_fd(list->fd_in);
	printf("fd_out : ");
	print_fd(list->fd_out);
	printf("fd_err : ");
	print_fd(list->fd_err);
	printf("\n");
}
