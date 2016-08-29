#include "sh21.h"

void	previous_word(t_data *data)
{
	if (!(data->mode_copy))
	{
		while (data->index > 0 && data->cmd[data->index - 1] != '\n' && \
		ft_isspace2(data->cmd[data->index - 1]))
			move_left_without_mod(data);
		while (data->index > 0 && data->cmd[data->index - 1] != '\n' && \
		!(ft_isspace2(data->cmd[data->index - 1])))
			move_left_without_mod(data);
	}
	else
	{
		while (data->index > 0 && data->cmd[data->index - 1] != '\n' && \
		ft_isspace2(data->cmd[data->index - 1]))
			move_left(data);
		while (data->index > 0 && data->cmd[data->index - 1] != '\n' && \
		!(ft_isspace2(data->cmd[data->index - 1])))
			move_left(data);
	}
}

void	next_word(t_data *data)
{
	if (!(data->mode_copy))
	{
		while (data->cmd[data->index] && !(ft_isspace2(data->cmd[data->index])))
			move_right_without_mod(data);
		while (data->cmd[data->index] && ft_isspace2(data->cmd[data->index]))
			move_right_without_mod(data);
	}
	else
	{
		while (data->cmd[data->index] && \
		!(ft_isspace2(data->cmd[data->index])) \
		&& data->index + 1 != (int)ft_strlen(data->cmd))
		{
			move_right(data);
		}
		while (data->cmd[data->index] && \
			ft_isspace2(data->cmd[data->index]) && \
		data->index + 1 != (int)ft_strlen(data->cmd))
			move_right(data);
	}
}
