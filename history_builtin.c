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
		data->history_flag[flag] = 1;
	return (flag);
}

void init_flag(t_data *data)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		data->history_flag[i] = 0;
		i++;
	}
}

int		get_history_flag(t_data *data, char **scmd, int *j, t_cmd *cmd)
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
				putstr_builtin(cmd, "42sh: history: usage: history [-c] [-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]\n", 2);
				return (1);
			}
		}
		(*j)++;
	}
	return (0);
}

int	history_flag_clear(t_data *data, char **scmd, t_cmd *cmd)
{
	if (data->history_flag[0])
		return (history_flag_c(data, cmd));
	else
		return (history_flag_d(data, scmd, cmd));
}

int	history_flag_file(t_data *data, char **scmd, t_cmd *cmd)
{
	if (data->history_flag[2])
		if (history_flag_a(data, scmd[0], cmd) == 1, cmd)
			return (0);
	if (data->history_flag[3])
		if (history_flag_w(data, scmd[0], cmd) == 1, cmd)
			return (0);
	if (data->history_flag[4])
		if (history_flag_r(data, scmd[0], cmd) == 1, cmd)
			return (0);
	if (data->history_flag[5])
		if (history_flag_n(data, scmd[0], cmd) == 1, cmd)
			return (0);
	return (1);
}

int	history_flag_weird(t_data *data, char **scmd, t_cmd *cmd)
{
	// char	*tmp_line;
	// int		tmp_time;
	// int		history_exist;
	//
	// history_exist = 0;
	// if (data->history != NULL)
	// {
		// tmp_line = ft_strdup(data->history->line);
		// tmp_time = data->history->time;
		// history_exist = 1;
	// }
	if (!scmd[0])
		return (1);
	if (data->history)
	{
		// printf("A KE KOUKOU --> [%s]\n", data->history->line);
		delete_last_history(data);
		// printf("A KE KOUKOU --> [%s]\n", data->history->line);
	}
	if (data->history_flag[6])
		if (history_flag_p(scmd, cmd) == 1)
			return (0);
	if (data->history_flag[7])
		if (history_flag_s(data, scmd, cmd) == 1)
			return (0);
	// if (history_exist)
	// {
	// 	data->history = add_history_elem(data->history, create_history_elem(tmp_line));
	// 	data->history->time = tmp_time;
	// }
	return (1);
}

int ft_history(char **scmd, t_data *data, t_cmd *cmd)
{
	int		j;

	j = 0;
	init_flag(data);
	printf("------------ JE PASSE DANS L'HISTORIQUE\n");
	if (get_history_flag(data, scmd, &j) == 1)
		return (1);
	// printf(" ---------------------- data->history = [%s]\n", data->history->line);
	// int	i = 0;
	// while (i < 9)
	// {
	// 	printf("Flag n°%d = %d\n", i, data->history_flag[i]);
	// 	i++;
	// }
	if (data->history_flag[0] || data->history_flag[1])
		return (history_flag_clear(data, scmd + j), cmd);
	else if (data->history_flag[2] || data->history_flag[3] || data->history_flag[4] || data->history_flag[5])
		return (history_flag_file(data, scmd + j, cmd));
	else if (data->history_flag[6] || data->history_flag[7])
		return (history_flag_weird(data, scmd + j, cmd));
	return (history_flag_none(data, scmd + j, cmd));
}
