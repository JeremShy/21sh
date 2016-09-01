/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:11:28 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 22:55:58 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem_fresh;

	mem_fresh = malloc(size);
	if (mem_fresh == NULL)
		return (NULL);
	if (size > 0)
	{
		ft_bzero(mem_fresh, size);
		return (mem_fresh);
	}
	return (0);
}
