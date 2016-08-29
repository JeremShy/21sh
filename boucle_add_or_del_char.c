#include <sh21.h>

int is_add_or_del_char(t_data *data, char buf[11])
{
	if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0' && !data->mode_copy)
	{
		if (data->list_auto)
		{
			delete_list_auto(data->list_auto);
			data->list_auto = NULL;
		}
		if (data->index == (int)data->real_len_cmd)
		{
			data->cmd = ft_strjoinaf1(data->cmd, buf);
			ft_putchar(buf[0]);
			data->index++;
		}
		else
			insert_mode(data, buf[0]);
		data->real_len_cmd++;
		data->first_search = 1;
		if (data->first)
		{
			free(data->first);
			data->first = NULL;
		}
	}
	else if (buf[0] == 127 && buf[1] == 0 && !data->mode_copy)
	{
		if (data->list_auto)
		{
			delete_list_auto(data->list_auto);
			data->list_auto = NULL;
		}
		if (data->index > 0)
		{
			delete_mode(data);
			data->first_search = 1;
			if (data->first)
			{
				free(data->first);
				data->first = NULL;
			}
			if (ft_strequ(data->cmd, ""))
				data->history_en_cours = NULL; // Voir si on veut le mettre
		}
	}
	else
		return (0);
	return (1);
}
