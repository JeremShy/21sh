/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 04:39:20 by adomingu          #+#    #+#             */
/*   Updated: 2015/10/14 04:54:09 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char *s, char *s1, char *s2)
{
	char	*ret;

	if (!s || !s1 || !s2 || !ft_strstr(s, s1))
		return (s);
	ret = (char *)malloc(sizeof(char) *\
			(ft_strlen(s) - ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_bzero(ret, ft_strlen(ret));
	ft_strncpy(ret, s, (ft_strstr(s, s1) - s));
	ft_strcat(ret, s2);
	ft_strcat(ret, ft_strstr(s, s1 + ft_strlen(s1)) + 1);
	return (ret);
}
