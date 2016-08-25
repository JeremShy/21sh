#include "sh21.h"

int		get_actual_line(t_data *data)
{
	return ((data->len_prompt + data->index + 1) / data->win_x);
}

int		get_line_max(t_data *data)
{
	return ((data->len_prompt + (int)ft_strlen(data->cmd) + 1) / data->win_x);
}

int		get_prompt_line(t_data *data)
{
	return (data->len_prompt / data->win_x);
}
