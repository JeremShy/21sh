/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_on.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:06:06 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 18:06:12 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void	*ft_go_on(void *str, int i)
{
	char	*tmp;

	tmp = (void*)ft_strdup((char*)str + i);
	free(str);
	return (tmp);
}
