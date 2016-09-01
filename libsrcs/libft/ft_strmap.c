/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:13:47 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/10 17:13:48 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*mem_fresh;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	mem_fresh = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i])
	{
		mem_fresh[i] = f(s[i]);
		i++;
	}
	mem_fresh[i] = '\0';
	return (mem_fresh);
}
