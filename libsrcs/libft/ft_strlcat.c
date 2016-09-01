/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:24:26 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/10 14:33:19 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	k = 0;
	while (src[k])
		k++;
	j = 0;
	while (dst[j] && j < size)
		j++;
	if (j >= size)
		return (size + k);
	len = (unsigned int)(j + k);
	i = 0;
	while (j < (size - 1) && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (len);
}
