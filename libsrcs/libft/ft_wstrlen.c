/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_wstrlen(const char *s)
{
	size_t	i;
	int		b;
	int		count;

	i = 0;
	count = 0;
	b = 0;
	while (s[i] != '\0')
	{
		if (s[i] > 0)
			count++;
		else
			b++;
		if (b == 3)
		{
			count++;
			b = 0;
		}
		i++;
	}
	return (count);
}
