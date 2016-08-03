#include <sh21.h>

int	is_history_flag(t_data *data, char car)
{
	int		flag;

	flag = -1;
	if (car == 'c')
		flag = 0;
	else if (car == 'd')
		flag = 1;
	else if (car == 'a')
		flag = 2;
	else if (car == 'w')
		flag = 3;
	else if (car == 'r')
		flag = 4;
	else if (car == 'n')
		flag = 5;
	else if (car == 'p')
		flag = 6;
	else if (car == 's')
		flag = 7;
	if (flag > -1)
		data->history_flag[flag] = 0;
	return (flag);
}

void init_flag(t_data *data)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		data->history_flag[i] = 1;
		i++;
	}
}

int		get_history_flag(t_data *data, char **scmd, int *j)
{
	int	i;

	while (scmd[*j] != NULL && scmd[*j][0] == '-')
	{
		i = 1;
		if (scmd[*j][1] == '\0')
			return (1);
		while (scmd[*j][i] != '\0')
		{
			if (is_history_flag(data, scmd[*j][i]) > -1)
				i++;
			else
			{
				ft_putstr_fd("42sh: history: usage: history [-c] [-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]\n", 2);
				return (1);
			}
		}
		(*j)++;
	}
	return (0);
}

int	history_flag_clear(t_data *data)
{
	if (data->history_flag[1] == 0)
		return (history_flag_c(data));
	else
		return (history_flag_d(data));
}

int	history_flag_file(t_data *data)
{
	if (data->history_flag[2] == 0)
		if (history_flag_a(data) == 1)
			return (1);
	if (data->history_flag[3] == 0)
		if (history_flag_w(data) == 1)
			return (1);
	if (data->history_flag[4] == 0)
		if (history_flag_r(data) == 1)
			return (1);
	if (data->history_flag[5] == 0)
		if (history_flag_n(data) == 1)
			return (1);
	return (0);
}

int	history_flag_weird(t_data *data)
{
	if (data->history_flag[6] == 0)
		if (history_flag_p(data) == 1)
			return (1);
	if (data->history_flag[7] == 0)
		if (history_flag_s(data) == 1)
			return (1);
	return (0);
}

int ft_history(char **scmd, t_data *data)
{
	int		j;

	j = 0;
	init_flag(data);
	if (get_history_flag(data, scmd, &j) == 1)
		return (1);
	if (scmd[j] == NULL)
		return (history_flag_none(data));
	else if (data->history_flag[0] || data->history_flag[1])
		return (history_flag_clear(data));
	else if (data->history_flag[2] || data->history_flag[3] || data->history_flag[4] || data->history_flag[5])
		return (history_flag_file(data));
	else if (data->history_flag[6] || data->history_flag[7])
		return (history_flag_weird(data));
	return (0);
}
