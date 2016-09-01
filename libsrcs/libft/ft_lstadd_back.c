/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 20:49:21 by sbenning          #+#    #+#             */
/*   Updated: 2014/11/16 19:54:05 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **alst, t_list *elem)
{
	t_list		*drive;

	if (!elem || !alst)
		return ;
	drive = *alst;
	if (drive)
	{
		while (drive->next)
			drive = drive->next;
		drive->next = elem;
	}
	else
		*alst = elem;
}
