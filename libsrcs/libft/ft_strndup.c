/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 14:27:35 by adomingu          #+#    #+#             */
/*   Updated: 2015/01/19 14:35:36 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*dst;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i <= n)
		i++;
	dst = (char *)malloc(sizeof(char) * (i + 1));
	if (dst)
	{
		i = 0;
		while (s1[i] && i <= n)
		{
			dst[i] = s1[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
