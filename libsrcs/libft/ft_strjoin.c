/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:13:34 by adomingu          #+#    #+#             */
/*   Updated: 2015/08/25 01:56:51 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem_fresh;
	size_t	n;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	else if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	n = ft_strlen(s1) + ft_strlen(s2);
	mem_fresh = (char *)malloc(sizeof(char) * n + 1);
	if (mem_fresh == NULL)
		return (NULL);
	ft_strcpy(mem_fresh, s1);
	ft_putchar(8);
	ft_strcat(mem_fresh, s2);
	return (mem_fresh);
}
