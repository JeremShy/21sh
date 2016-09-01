/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ret;

	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	if (content_size == 0 || content == NULL)
	{
		ret->content = NULL;
		ret->content_size = 0;
	}
	else
	{
		ret->content = malloc(sizeof(content));
		if (ret->content == NULL)
			return (NULL);
		ft_memcpy(ret->content, content, sizeof(content));
		ret->content_size = content_size;
	}
	ret->next = NULL;
	return (ret);
}
