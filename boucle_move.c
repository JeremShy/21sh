#include <sh21.h>

static void	real_page_up(t_data *data)
{
	if (data->list_auto)
		delete_list_auto(data->list_auto);
	data->list_auto = NULL;
	page_up(data);
}

static void	real_page_down(t_data *data)
{
	if (data->list_auto)
		delete_list_auto(data->list_auto);
	data->list_auto = NULL;
	page_down(data);
}

static void	real_previous_word(t_data *data)
{
	if (data->list_auto)
	{
		delete_list_auto(data->list_auto);
		data->list_auto = NULL;
	}
	previous_word(data);
}

static void	real_next_word(t_data *data)
{
	if (data->list_auto)
	{
		delete_list_auto(data->list_auto);
		data->list_auto = NULL;
	}
	next_word(data);
}

int			is_boucle_move(t_data *data, char *buf)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
		move_left(data);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0)
		move_right(data);
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && buf[3] == 0) ||
			(buf[0] == 1 && buf[1] == 0))
		boucle_home(data);
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 70 && buf[3] == 0) ||
			(buf[0] == 5 && buf[1] == 0))
		boucle_end(data);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 53
		&& buf[3] == 126 && buf[4] == 0)
		real_page_up(data);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 54
		&& buf[3] == 126 && buf[4] == 0)
		real_page_down(data);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68
		&& buf[4] == 0)
		real_previous_word(data);
	else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67
		&& buf[4] == 0)
		real_next_word(data);
	else
		return (0);
	return (1);
}
