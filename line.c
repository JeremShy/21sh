/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:19:00 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/20 00:10:02 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void move_left_simple(t_data *data)
{
	exec_tcap("le");
	data->curs_x--;
	data->index--;
}

void move_right_simple(t_data *data)
{
	exec_tcap("nd");
	data->curs_x++;
	data->index++;
}

int get_actual_line(t_data *data)
{
	return((data->len_prompt + data->index + 1) / data->win_x);
}

int	get_actual_cursor(t_data *data)
{
	return ((data->len_prompt + data->index) % (data->win_x));
}

int	get_line_max(t_data *data)
{
	return ((data->len_prompt + (int)ft_strlen(data->cmd) + 1) / data->win_x);
}

int	can_move_up(t_data	*data)
{
	int line_prompt;

	line_prompt = data->len_prompt / data->win_x;
	if (get_actual_line(data) > line_prompt)
		return (1);
	return (0);
}

int can_move_down(t_data *data)
{
	if (get_actual_line(data) < get_line_max(data))
		return (1);
	return (0);
}

int get_prompt_line(t_data *data)
{
	return (data->len_prompt / data->win_x);
}

void	insert_mode(t_data *data, char c)
{
	int	new_index;

	new_index = data->index + 1;
 	data->cmd = insert_char(data->cmd, data->index, c);
	ft_putstr(data->cmd + data->index);
	// if (data->win_x == get_actual_cursor(data) + (int)ft_strlen(data->cmd + data->index))
	// 	ft_putchar(' ');
	data->index = (int)ft_strlen(data->cmd);
	//FAIRE LES MOVES LEFTS
	while(data->index > new_index)
	{
		// sleep(1);
		move_left(data);
	}
	// if (get_line_max(data) == get_actual_line(data) && get_actual_cursor(data) == data->win_x)
	// 	ft_putchar(' ');
	// data->index = old_index;
}

void delete_mode(t_data *data)
{
	int	index;

//abcdefghijklmnopqrstuvwxyz
	move_left(data);
	// printf("CALCUL CHELOU = %d\n", (data->len_prompt + data->index + 1) % (data->win_x));
	// exec_tcap("vb");
	if ((data->len_prompt + data->index + 1) % (data->win_x) == 0)
		exec_tcap("ce");
	index = data->index + 1;
	exec_tcap("cd");
	ft_putstr(data->cmd + data->index + 1);
	data->cmd = delete_char(data->cmd, data->index + 1);
	// exec_tcap("cd");
	data->index = ft_strlen(data->cmd);
	// printf("FIRST COND = %d ///// SECOND = %d\n", get_actual_cursor(data), (int)ft_strlen(data->cmd));
	if (get_actual_cursor(data) == 0 && data->index == (int)ft_strlen(data->cmd))
	{
		move_left_simple(data);
		move_right_simple(data);
	}
	// data->index = data->index - 1;// HOTFIX DEGUEU
	// printf("get_actual_cursor(data) = %d\n", get_actual_cursor(data));
	// if (data->win_x == get_actual_cursor(data) + (int)ft_strlen(data->cmd + index))
		// ft_putchar(' ');
	// data->index = data->index + 1; // TOUJOURS DEGUEU
	while (data->index > index)
	{
		move_left(data);
	}
	if (data->index != (int)ft_strlen(data->cmd))
		move_left(data);
	if (index == (int)ft_strlen(data->cmd))
	{
		// printf("caca\n");
		move_left(data);
	}
}

void move_r2l(t_data *data)
{
	int		i;

	i = 0;
	exec_tcap("do");
	exec_tcap("cr");
	// while (i < (int)ft_strlen(data->cmd))
	// {
	// 	exec_tcap("nd");
	// 	i++;
	// }
	data->index++;
}

void	move_l2r(t_data *data)
{
	int	i;

	exec_tcap("up");
	exec_tcap("cr");
	i = 0;
	while (i < data->win_x)
	{
		// move_right(data);
		exec_tcap("nd");
		i++;
	}
	data->index--;
}

void	move_left(t_data *data)
{
	if (get_actual_line(data) > get_prompt_line(data)) // Si on est pas sur la premiere ligne
	{
		if (get_actual_cursor(data) > 0)
			move_left_simple(data);
		else if (get_actual_cursor(data) == 0 && data->index == (int)ft_strlen(data->cmd))
		{
			move_left_simple(data);
			// move_right_simple(data);
			exec_tcap("nd");
		}
		else
			// move_left_simple(data);
			// exec_tcap("vb");
			move_l2r(data);
	}
	else
	{
		if (data->index > 0)
		// if (get_actual_cursor(data) > (data->len_prompt) % data->win_x)
		{
			move_left_simple(data);
		}
		else
			exec_tcap("vb");
	}
}


void move_right(t_data *data)
{
	// if (data->curs_x < data->len_prompt + 1 + (int)data->real_len_cmd)
	// 	move_right(data);
	if (data->index < (int)ft_strlen(data->cmd))
	{
		if (get_actual_cursor(data) + 1 == data->win_x)
		{
			move_r2l(data);
		}
		else
		{
			move_right_simple(data);
		}
	}
	else
		// printf("get_actual_cursor(data) = [%d] /// data->win_x = [%d]\n", get_actual_cursor(data), data->win_x);
		// printf("data->index : %d - strltruc %zu\n", data->index, ft_strlen(data->cmd));
		exec_tcap("vb");
}
