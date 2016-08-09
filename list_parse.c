#include <sh21.h>

void		print_list(t_cmd *lst)
{
	size_t	i;
	char		**av;
	size_t	j;

	i = 0;
	while (lst != NULL)
	{
		printf("list number : %zu\n", i);
		av = lst->av;
		j = 0;
		while (av[j])
		{
			printf("av[%zu] : #%s#\n", j, av[j]);
			j++;
		}
		// printf("sep : %c\n", lst->sep);
		i++;
		print_fd_list(lst);
		lst = lst->next;
		printf("\n");
	}
}

t_cmd	*create_cmd_elem(char *str, int count, t_hc **heredocs)
{
	t_cmd		*elem;

	elem = (t_cmd*)malloc(sizeof(t_cmd)); // On alloue l'espace necessaire à la contiendance de notre élément.
	elem->fd_in = create_fd(-1); // On initialise les trois fds.
	elem->fd_out = create_fd(-1);
	elem->fd_err = create_fd(-1);
	// printf("str : [%s]\n", str);
	elem->p_error	= 0;
	elem->error = 0;
	elem->sep = NONE;
	printf("STR3 = [%s]\n", str);
	if (split_cmd(count, &str, elem, heredocs) == -1)
	{
		//faire quelque
		printf("ARGH\n");
		return (NULL);
	}
	// printf("sep : %d\n", elem->sep);
	// printf("on cree une liste.\n");
	elem->next = NULL;
	if (elem->fd_in->fd == -1)
		elem->fd_in->fd = 0;
	if (elem->fd_out->fd == -1)
		elem->fd_out->fd = 1;
	if (elem->fd_err->fd == -1)
		elem->fd_err->fd = 2;
	// printf("KUKOU, CA FREEZ\n");
 	free(str);
	// print_fd_list(elem);
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem) //Ça add.
{
	t_cmd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}
