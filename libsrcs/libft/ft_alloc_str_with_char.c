/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_str_with_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_alloc_str_with_char(int c)
{
	char	*ret;

	ret = (char*)malloc(2 * sizeof(char));
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
