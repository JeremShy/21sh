/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vid_inv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/25 21:36:15 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/28 16:40:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	vi_char(char c)
{
	exec_tcap("mr");
	ft_putchar(c);
	exec_tcap("me");
}

void	vi_str(char *s)
{
	exec_tcap("mr");
	ft_putstr(s);
	exec_tcap("me");
}

void	vi_str_free(char *s)
{
	exec_tcap("mr");
	ft_putstr(s);
	exec_tcap("me");
	free(s);
}

void	move_left_without_mod(t_data *data)
{
	if (data->index == 0 || data->cmd[data->index - 1] == '\n')
		return ;
	if (data->index_min_win != -1 && data->index_min_win == data->index)
	{
		printf("MDR GROS CON\n");
		exec_tcap("vb");
		return ;
	}
	if (get_actual_line(data) > get_prompt_line(data)) // Si on est pas sur la premiere ligne
	{
		if (get_actual_cursor(data) > 0)
			move_left_simple(data);
		else if (get_actual_cursor(data) == 0 && data->index == (int)ft_strlen(data->cmd))
		{
			move_left_simple(data);
			exec_tcap("nd");
		}
		else
			move_l2r(data);
	}
	else
	{
		if (data->index > 0)
		{
			move_left_simple(data);
		}
		else
			exec_tcap("vb");
	}
}

void move_right_without_mod(t_data *data)
{
	if (data->index == (int)ft_strlen(data->cmd))
	{
		exec_tcap("vb");
		return ;
	}
	if (get_actual_cursor(data) + 1 == data->win_x && data->index == (int)ft_strlen(data->cmd) - 1)
	{
		ft_putchar(data->cmd[data->index]);
		data->index++;
	}
	else if (data->index < (int)ft_strlen(data->cmd))
	{
		if (get_actual_cursor(data) + 1 == data->win_x)
			move_r2l(data);
		else
			move_right_simple(data);
	}
}