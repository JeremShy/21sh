/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int						i;
	unsigned const char		*ch1;
	unsigned const char		*ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	i = 0;
	while (i < (int)n)
	{
		if (ch1[i] == ch2[i])
			i++;
		else
			return ((unsigned char)ch1[i] - (unsigned char)ch2[i]);
	}
	return (0);
}
