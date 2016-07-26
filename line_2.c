/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 18:31:23 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/27 00:19:01 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	page_up(t_data *data)
{
	int	verif_new_line;

	if (data->index - data->win_x >= 0 && !(get_actual_cursor(data) == 0 && (int)ft_strlen(data->cmd) == data->index))
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
				move_left_without_mod(data);
				verif_new_line--;
			}
			if (data->mode_copy)
			{
				verif_new_line = data->index;
				if (data->index_min_copy > data->index_max_copy)
					data->index_max_copy = data->index_min_copy;
				while (data->cmd[data->index] && data->index <= data->index_max_copy)
				{
					exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					data->index++;
				}
				exec_tcap("me");
				while (data->index > verif_new_line)
					move_left_without_mod(data);
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
			if (data->mode_copy == 0)
			{
				write(1, data->cmd + data->index, data->win_x); // OPTI TU PEUX PAS TEST
				data->index += data->win_x;
			}
			else
			{
				if (data->index_min_copy > data->index_max_copy)
					data->index_max_copy = data->index_min_copy;
				verif_new_line = data->index + data->win_x;
				while (data->index < verif_new_line)
				{
					if (data->index_min_copy == data->index || data->index_max_copy == data->index)
						exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					if (data->index_max_copy == data->index)
						exec_tcap("me");
					data->index++;
				}
			}
			// while (verif_new_line > 0)
			// {
			// 	move_right(data);
			// 	verif_new_line--;
			// }
		}
	}
}
