/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:29:36 by jcamhi            #+#    #+#             */
/*   Updated: 2015/11/24 14:46:22 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*res;

	res = (char*)malloc(size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
		res[i++] = '\0';
	return (res);
}
