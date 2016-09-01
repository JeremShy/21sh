/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 22:34:23 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 22:56:58 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newe;
	t_list	*tmp;

	tmp = NULL;
	newe = tmp;
	while (lst)
	{
		if (f)
			tmp = f(lst);
		ft_lstaddlast(&newe, tmp);
		lst = lst->next;
	}
	return (newe);
}
