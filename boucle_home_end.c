/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:06 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	boucle_home(t_data *data)
{
	if (data->list_auto)
	{
		delete_list_auto(data->list_auto);
		data->list_auto = NULL;
	}
	if (data->mode_copy && data->index == data->index_max_copy)
		data->index_max_copy = data->index_min_copy;
	while (data->index > 0 && data->cmd[data->index - 1] != '\n')
		move_left_without_mod(data);
	if (data->mode_copy)
	{
		data->index_min_copy = data->index;
		while (data->cmd[data->index])
		{
			if (data->index == data->index_min_copy
				|| data->index == data->index_max_copy)
				exec_tcap("mr");
			ft_putchar(data->cmd[data->index]);
			if (data->index == data->index_max_copy)
				exec_tcap("me");
			data->index++;
		}
		while (data->index > 0 && data->cmd[data->index - 1] != '\n')
			move_left_without_mod(data);
	}
}

void	boucle_end(t_data *data)
{
	reinit_list_auto(data);
	if (data->mode_copy)
	{
		if (data->index_min_copy == data->index)
			data->index_min_copy = data->index_max_copy;
		data->index_max_copy = (int)ft_strlen(data->cmd) - 1;
		if (data->index > data->index_min_copy)
			exec_tcap("mr");
		while (data->cmd[data->index] && data->cmd[data->index + 1])
		{
			if (data->index == data->index_min_copy)
				exec_tcap("mr");
			ft_putchar(data->cmd[data->index]);
			if (data->index == data->index_max_copy)
				exec_tcap("me");
			data->index++;
		}
		exec_tcap("me");
	}
	else
	{
		ft_putstr(data->cmd + data->index);
		data->index = (int)ft_strlen(data->cmd);
	}
}
