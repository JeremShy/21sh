/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:52:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/04/01 20:13:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void boucle(t_env *env)
{
	char	buf[6];
	int		r;

	while ((r = read(0, buf, 5)))
	{
		env = NULL;
		buf[r] = '\0';
		if (isalpha(buf[0]) && buf[1] == '\0')
			ft_putchar(buf[0]);
		else
			ft_printf("%d - %d- %d - %d - %d - %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
	}
}