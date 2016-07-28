/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 18:31:23 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/28 23:09:41 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	page_up(t_data *data)
{
	int	verif_new_line;
	int	tmp;
	int	old_index;

	if (data->index - data->win_x >= 0 && !(get_actual_cursor(data) == 0 && (int)ft_strlen(data->cmd) == data->index))
	{
		old_index = data->index;
		verif_new_line = data->win_x;
		while (verif_new_line > 0 && data->cmd[data->index - verif_new_line] != '\n')
			verif_new_line--;
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
				tmp = data->index_max_copy;
				if (old_index != data->index_min_copy)
				{
					if (data->index_max_copy - data->win_x < data->index_min_copy)
					{
						verif_new_line = data->index_min_copy;
						data->index_min_copy = data->index_max_copy - data->win_x;
						data->index_max_copy = verif_new_line;
					}
					else
					{
						data->index_max_copy -= data->win_x;
					}
				}
				else
				{
					data->index_min_copy -= data->win_x;
				}
				verif_new_line = data->index;
				if (data->index > data->index_min_copy && data->index <= data->index_max_copy)
					exec_tcap("mr");
				while (data->cmd[data->index] && data->index <= tmp)
				{
					if (data->index == data->index_min_copy)
						exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					if (data->index == data->index_max_copy)
						exec_tcap("me");
					data->index++;
				}
				exec_tcap("me");
				if (data->index > verif_new_line)
				{
					if (get_actual_cursor(data) == 0)
					{
						exec_tcap("le");
						exec_tcap("nd");
						data->index--;
					}
					else
						move_left_without_mod(data);
				}
				while (data->index > verif_new_line)
					move_left_without_mod(data);
			}
		}
		else
			exec_tcap("vb");
	}
}

void page_down(t_data *data)
{
	int	tmp;
	int why;

	if ((data->index + data->win_x < (int)ft_strlen(data->cmd)
			|| (get_actual_cursor(data) != 0 && data->index + data->win_x == (int)ft_strlen(data->cmd)))
 		&& !(data->mode_copy && data->index + data->win_x == (int)ft_strlen(data->cmd))) // On verifie qu'on peut bien aller vers le bas et que le curseur ne puisse pas aller au bout de la chaine si on est en mode_copy.
	{
		why = 0;
		if (data->mode_copy == 0) // Si on est pas en mode_copy..
		{
			write(1, data->cmd + data->index, data->win_x); // OPTI TU PEUX PAS TEST
			data->index += data->win_x;
		}
		else // Sinon..
		{
			if (data->index == data->index_min_copy && data->index_min_copy + data->win_x <= data->index_max_copy)
			{
				data->index_min_copy = data->index_min_copy + data->win_x;
				why = 1;
			}
			else if (data->index == data->index_min_copy && data->index_max_copy != data->index_min_copy) // Si on est dans la situation ou le curseur est en arriere de la position de depart
			{
				tmp = data->index_min_copy;
				data->index_min_copy = data->index_max_copy;
				data->index_max_copy = tmp + data->win_x;
			}
			else // L'autre cas
			{
				data->index_max_copy += data->win_x;
				if (data->index >= data->index_min_copy && data->index <= data->index_max_copy)
					exec_tcap("mr");
			}
			tmp = data->index + data->win_x;
			while (data->index <= tmp)
			{
				if (data->index_min_copy == data->index)
					exec_tcap("mr");
				ft_putchar(data->cmd[data->index]);
				if (data->index_max_copy == data->index)
					exec_tcap("me");
				data->index++;
			}
			why ? exec_tcap("me") : 0;
			if (get_actual_cursor(data) == 0)
			{
				exec_tcap("le");
				exec_tcap("nd");
				data->index--;
			}
			else
				move_left_without_mod(data);
		}
	}
}

//abcdefghijklmnopqrstuvwxyz
