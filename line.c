/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:19:00 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/27 16:08:12 by jcamhi           ###   ########.fr       */
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

// int	get_actual_cursor(t_data *data)
// {
// 	return ((data->len_prompt + data->index) % (data->win_x));
// }

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
	data->index = (int)ft_strlen(data->cmd);
	while(data->index > new_index)
	{
		move_left(data);
	}
}

void delete_mode(t_data *data)
{
	int	index;

//abcdefghijklmnopqrstuvwxyz
	if (data->index == 0 || data->cmd[data->index - 1] == '\n')
		return ;
	if (data->index_min_win != -1 && data->index_min_win == data->index)
	{
		// printf("MIN WIN DETECTED\n");
		exec_tcap("vb");
		return ;
	}
	move_left(data);
	if ((data->len_prompt + data->index + 1) % (data->win_x) == 0)
		exec_tcap("ce");
	index = data->index + 1;
	exec_tcap("cd");
	ft_putstr(data->cmd + data->index + 1);
	data->cmd = delete_char(data->cmd, data->index + 1);
	data->index = ft_strlen(data->cmd);
	if (get_actual_cursor(data) == 0 && data->index == (int)ft_strlen(data->cmd))
	{
		move_left_simple(data);
		ft_putchar(data->cmd[data->index - 1]);
		data->index++;
	}
	while (data->index > index)
	{
		move_left(data);
	}
	if (data->index != (int)ft_strlen(data->cmd))
		move_left(data);
	if (index == (int)ft_strlen(data->cmd))
	{
		move_left(data);
	}
}

int	get_actual_cursor(t_data *data)
{
	int	x;
	int	i;

	x = 0;
	i = 0;

	while (data->prompt[i] != '\0')
	{
		if (data->prompt[i] == '\n')
			x = 0;
		else if (x == data->win_x)
			x = 0;
		else
			x++;
		i++;
	}
	i = 0;
	while (data->cmd[i] != '\0' && i < data->index)
	{
		if (data->cmd[i] == '\n')
			x = 0;
		else if (x == data->win_x - 1)
			x = 0;
		else
			x++;
		i++;
	}
	return (x);
}

void move_r2l(t_data *data)
{
	int		i;

	i = 0;
	exec_tcap("do");
	exec_tcap("cr");
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
		exec_tcap("nd");
		i++;
	}
	data->index--;
}

void	move_left(t_data *data)
{
	if (data->index == 0 || data->cmd[data->index - 1] == '\n')
		return ;
	if (data->index_min_win != -1 && data->index_min_win == data->index)
	{
		printf("MDR GROS CON\n");
		exec_tcap("vb");
		return ;
	}
	if (data->mode_copy && data->index == data->index_max_copy && data->index_min_copy != data->index_max_copy) // Le left quand on est a l'extreme droite (#JMLP)
	{
		ft_putchar(data->cmd[data->index]);
		data->index++;
		move_left_without_mod(data);
		data->index_max_copy--;
	}
	else if (data->mode_copy && data->index == data->index_min_copy)
		data->index_min_copy--;
	move_left_without_mod(data);
	if (data->mode_copy)
	{
		vi_char(data->cmd[data->index]);
		data->index++;
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

void move_right(t_data *data)
{
	if ((data->mode_copy && data->index + 1 == (int)ft_strlen(data->cmd)) || (data->mode_copy == 0 && data->index == (int)ft_strlen(data->cmd)))
	{
		exec_tcap("vb");
		return ;
	}
	if (data->mode_copy && data->index == data->index_min_copy && data->index_min_copy != data->index_max_copy)
	{
		ft_putchar(data->cmd[data->index]);
		data->index++;
		if (get_actual_cursor(data) == 0)
		{
			ft_putchar(data->cmd[data->index]);
			data->index++;
			move_left_without_mod(data);
			move_left_without_mod(data);
		}
		else
		{
			move_left_without_mod(data);
		}
		data->index_min_copy++;
	}
	else
		data->index_max_copy++;
	move_right_without_mod(data);
	if (data->mode_copy)
	{
		vi_char(data->cmd[data->index]);
		data->index++;
		if (get_actual_cursor(data) == 0)
		{
			ft_putchar(data->cmd[data->index]);
			data->index++;
			move_left_without_mod(data);
			move_left_without_mod(data);
		}
		else
		{
			move_left_without_mod(data);
		}
	}
}
