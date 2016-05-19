/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:52:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/05/19 15:11:09 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	boucle(t_env *env, t_data *data)
{
	env = NULL;
	
	char	buf[6];
	int		r;

	ft_bzero(buf, 6);
	while ((r = read(0, buf, 5)))
	{
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0')
		{
			ft_putchar(buf[0]);
			data->curs_x++;
		}
		else if (buf[0] == 4 && buf[1] == 0)
			exit(0);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
		{
			if (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
			{
				exec_tcap("le");
				data->curs_x--;
			}
		}
		else
		{
			ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		ft_bzero(buf, 6);
	}
}
