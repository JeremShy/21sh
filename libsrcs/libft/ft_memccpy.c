/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dst,
		const void *src, int c, size_t n)
{
	unsigned char	*curdst;
	unsigned char	*cursrc;
	int				i;

	curdst = (unsigned char *)dst;
	cursrc = (unsigned char *)src;
	i = 0;
	while (i < (int)n)
	{
		*curdst = *cursrc;
		if (*cursrc == (unsigned char)c)
			return (curdst + 1);
		i++;
		curdst++;
		cursrc++;
	}
	return (NULL);
}
