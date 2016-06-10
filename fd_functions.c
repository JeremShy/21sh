/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 15:41:35 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/09 18:31:01 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_fd	*create_fd(int fd)
{
	t_fd	*elem;

	elem = (t_fd*)malloc(sizeof(t_fd));
	elem->next = NULL;
	elem->fd = fd;
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
	return (tmp);
}

t_fd	*copy_list_fd(t_fd *list)
{
	t_fd	*new_list;

	new_list = NULL;
	while (list)
	{
		new_list = add_fd_elem(new_list, create_fd(list->fd));
		list = list->next;
	}
	return (new_list);
}
