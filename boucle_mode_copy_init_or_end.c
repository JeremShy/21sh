#include <sh21.h>

static void	init_mode_copy(t_data *data)
{
	int origin;

	data->index_min_copy = data->index;
	data->index_max_copy = data->index;
	origin = data->index;
	vi_char(data->cmd[data->index]);
	data->index++;
	while (data->cmd[data->index])
	{
		ft_putchar(data->cmd[data->index]);
		data->index++;
	}
	while (data->index > origin)
		move_left(data);
	data->mode_copy = 1;
}

static void	end_mode_copy(t_data *data)
{
	int	origin;

	origin = data->index;
	data->mode_copy = 0;
	while (data->index > 0 && data->cmd[data->index - 1] != '\n')
		move_left_without_mod(data);
	ft_putstr(data->cmd + data->index);
	data->index = (int)ft_strlen(data->cmd);
	while (data->index > origin)
		move_left_without_mod(data);
}

void		init_or_end_mode_copy(t_data *data)
{
	if (data->list_auto)
	{
		delete_list_auto(data->list_auto);
		data->list_auto = NULL;
	}
	if (data->mode_copy == 0 && data->cmd[0] != '\0'
		&& data->index != (int)ft_strlen(data->cmd))
		init_mode_copy(data);
	else
		end_mode_copy(data);
}
