/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 18:31:23 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/25 18:33:08 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	page_up(t_data *data)
{
	int	verif_new_line;

	if (data->index - data->win_x >= 0 && !(get_actual_cursor(data) == 0 && (int)ft_strlen(data->cmd) == data->index	))
	{
		verif_new_line = data->win_x;
		while (verif_new_line > 0)
		{
			if (data->cmd[data->index - verif_new_line] == '\n')
				break ;
			verif_new_line--;
		}
		if (verif_new_line == 0)
		{
			verif_new_line = data->win_x;
			while (verif_new_line > 0)
			{
				move_left(data);
				verif_new_line--;
			}
		}
	}
}

void page_down(t_data *data)
{
	int	verif_new_line;

	if (data->index + data->win_x < (int)ft_strlen(data->cmd) || (get_actual_cursor(data) != 0 && data->index + data->win_x == (int)ft_strlen(data->cmd)))
	{
		// printf("C BO\n");
		verif_new_line = data->win_x;
		while (verif_new_line > 0)
		{
			if (data->cmd[data->index + verif_new_line] == '\n')
				break ;
			verif_new_line--;
		}
		if (verif_new_line == 0)
		{
			verif_new_line = data->win_x;
			while (verif_new_line > 0)
			{
				move_right(data);
				verif_new_line--;
			}
		}
	}
}
