/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 21:24:53 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/10 21:36:57 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s2);
	if (!s2)
		return ((char *)s1);
	while (s1[i] && i + len <= n)
	{
		if (ft_strncmp(s1 + i, s2, len) == 0)
			break ;
		i++;
	}
	if (i + len <= n && ft_strncmp(s1 + i, s2, len) == 0)
		return ((char *)s1 + i);
	return (NULL);
}
