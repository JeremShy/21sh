/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 22:55:58 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/02 16:10:10 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*mallocp(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}
