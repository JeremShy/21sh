/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_join_src.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 11:59:29 by adomingu          #+#    #+#             */
/*   Updated: 2015/01/19 12:03:37 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_join_src(char *dst, char **src)
{
	char	*tmpl;

	tmpl = ft_strjoin(dst, *src);
	ft_strdel(src);
	return (tmpl);
}
