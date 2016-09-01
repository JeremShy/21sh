/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:21:45 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/03 21:21:48 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (src && dst && s[i] != (unsigned char)c && i < n)
	{
		d[i] = s[i];
		i++;
	}
	if (src && dst && s[i] == (unsigned char)c && i < n)
	{
		d[i] = s[i];
		i++;
		return (dst + i);
	}
	else
		return (NULL);
}
