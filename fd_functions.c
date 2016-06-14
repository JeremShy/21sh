/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 15:41:35 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 18:44:48 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

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
	printf("fd_in : \n");
	print_fd(list->fd_in);
	printf("fd_out : \n");
	print_fd(list->fd_out);
	printf("fd_err : \n");
	print_fd(list->fd_err);
	printf("\n");
}

t_fd	*create_fd(int fd)
{
	t_fd	*elem;

	elem = (t_fd*)malloc(sizeof(t_fd));
	elem->next = NULL;
	elem->fd = fd; //
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
		copy = add_fd_elem(copy, create_fd(dup(list->fd)));
		list = list->next;
	}
	return (copy);
}
