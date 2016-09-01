/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:24:48 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 15:20:05 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst != NULL)
	{
		while (src[i] != '\0' && i < n)
		{
			dst[i] = src[i];
			i++;
		}
		while (i < n)
			dst[i++] = '\0';
		return (dst);
	}
	return (NULL);
}
