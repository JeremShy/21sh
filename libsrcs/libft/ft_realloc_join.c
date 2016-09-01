/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 17:32:14 by adomingu          #+#    #+#             */
/*   Updated: 2015/01/19 11:59:11 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_join(char **dst, char *src)
{
	char	*tmpl;

	tmpl = ft_strjoin(*dst, src);
	ft_strdel(dst);
	return (tmpl);
}
