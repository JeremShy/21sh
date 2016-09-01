/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:52:54 by adomingu          #+#    #+#             */
/*   Updated: 2014/11/18 23:02:30 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*mem_fresh;
	char	c;
	char	*tmp;

	if (!s || strlen(s) < len)
		return (NULL);
	tmp = ft_strdup(s);
	c = tmp[start + len];
	tmp[start + len] = '\0';
	mem_fresh = ft_strdup(tmp + start);
	tmp[start + len] = c;
	free(tmp);
	return (mem_fresh);
}
