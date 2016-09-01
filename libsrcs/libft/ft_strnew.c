/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:52:13 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 14:40:09 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*mem_fresh;

	mem_fresh = (char *)malloc(sizeof(char) * size + 1);
	if (mem_fresh == NULL)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		mem_fresh[i] = '\0';
		i++;
	}
	return (mem_fresh);
}
