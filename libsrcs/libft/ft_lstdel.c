/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 22:33:57 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 22:56:27 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst != NULL && *alst != NULL)
	{
		tmp = (*alst)->next;
		while (*alst != NULL && del != NULL)
		{
			ft_lstdelone(alst, del);
			*alst = tmp;
			if (*alst != NULL)
				tmp = (*alst)->next;
		}
	}
}
