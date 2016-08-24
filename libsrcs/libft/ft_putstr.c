/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:02:45 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/26 16:40:39 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void	ft_putstr(char *s)
{
	int i;

	if (s == NULL)
	{
		ft_putstr("(null)");
		return ;
	}
	i = ft_strlen(s);
	write(1, s, i);
}
