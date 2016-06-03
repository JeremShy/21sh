/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 12:51:49 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/03 13:07:12 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_history	*create_history_elem(char *content)
{
	static int	i = 1;
	t_history		*elem;

	elem = (t_history*)malloc(sizeof(t_history));
	elem->line = ft_strdup(content);
	elem->index = i;
	elem->next = NULL;
	elem->prec = NULL;
	return (elem);
}

t_history *add_history_elem(t_history *list, t_history *elem)
{
	if (list == NULL)
		return (elem);
	list->next = elem;
	elem->prec = list;
	return (elem);
}
