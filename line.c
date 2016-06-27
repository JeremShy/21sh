/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:19:00 by jcamhi            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/06/19 00:32:06 by adomingu         ###   ########.fr       */
=======
/*   Updated: 2016/06/27 22:30:27 by jcamhi           ###   ########.fr       */
>>>>>>> origin/vsteffen
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void move_left(t_data *data)
{
	if (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
	{
		exec_tcap("le");
		data->curs_x--;
		data->index--;
	}
}

void move_right(t_data *data)
{
	if (data->curs_x < data->len_prompt + 1 + (int)data->real_len_cmd)
	{
		exec_tcap("nd");
		data->curs_x++;
		data->index++;
	}
}

void delete_use(t_data *data)
{
	data->len_prompt = ft_strlen(data->prompt) + 1;
	// ft_putstr("passe");
	// printf("data->curs_x = %d, data->len_prompt = %d", data->curs_x, data->len_prompt);
	if (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
	{
		exec_tcap("le");
		data->curs_x--;
		data->cmd = delete_char(data->cmd, data->index);
		data->index--;
		data->real_len_cmd--;
		exec_tcap("dm");
		exec_tcap("dc");
		exec_tcap("ed");
	}
}
