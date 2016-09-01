/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:22:24 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/03 21:22:39 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*src;
	unsigned char			ch;

	i = 0;
	ch = (unsigned char)c;
	src = (unsigned char *)s;
	while (src && i < n && src[i] != ch)
		i++;
	if (src && src[i] == ch && i < n)
		return ((void *)s + i);
	return (NULL);
}
