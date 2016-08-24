#include <sh21.h>

void sigint(int sig)
{
  t_data  *data;

  sig = 0;
	(void)sig; // TODO set but not used
  data = singleton_data(NULL, 0);
  exec_tcap("me");
  while (data->index < (int)ft_strlen(data->cmd))
    move_right_without_mod(data);
  ft_putstr("\n");
  data->real_len_cmd = 0;
  if (data->first)
  {
    free(data->first);
    data->first = NULL;
  }
  data->first_search = 1;
  data->history_en_cours = NULL;
  free(data->cmd);
  data->cmd = ft_strdup("");
  data->index = 0;
  data->c = 0;
	free(data->prompt);
  data->prompt = print_prompt(data->env, data);
  data->len_prompt = ft_strlen(data->prompt);
	if (data->cmd_tmp) // TEST DE TRUC CHELOU
	{
		if (data->cmd_tmp[0])
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
		}
	}
	reinitialise_heredoc(data, 1);
  free(data->cmd_tmp);
  data->cmd_tmp = ft_strdup("");
	data->quote_old_index = 0;
  data->mode_copy = 0;
	data->list_auto = NULL;
	data->cmd_before_auto = NULL;
	if (data->absolute_cmd_before_auto)
		free(data->absolute_cmd_before_auto);
	data->absolute_cmd_before_auto = NULL;
	data->index_before_auto = 0;
  data->index_before_move = 0;
}

void get_winsize(t_data *data)
{
   struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	data->win_y = w.ws_row;
	data->win_x = w.ws_col;
	if (isatty(0)) // TODO zero division error if no prompt
		data->after_prompt = (data->len_prompt + 1) % data->win_x;
}

void clear_cmd(t_data	*data)
{
	int	j;
	int	old_index;
	int	i;

	old_index = data->index;
	(void)old_index; //TODO useless set
	exec_tcap("cr");
	i = get_actual_line(data);
	j = get_line_max(data);
	while(i < j)
	{
		exec_tcap("do");
		i++;
	}
	// sleep(3);
	j = get_line_max(data);
	while (j >= 0)
	{
		// exec_tcap("vb");
		exec_tcap("cd");
		exec_tcap("up");
		j--;
	}
	// sleep(3);
	j = 0;
	data->index = 0;
	i = 0;

	print_prompt(data->env, data);
	i = 0;
	while (i < (int)ft_strlen(data->cmd))
	{
		ft_putchar(data->cmd[i]);
		// printf("DATA->INDEX = %d /// get_actual_line = %d /// DATA->win_x = %d\n", data->index, get_actual_cursor(data), data->win_x);
		if (get_actual_cursor(data) + 1 == data->win_x)
		{
			// ft_putchar(' ');
			// exec_tcap("vb");
			exec_tcap("do");
			exec_tcap("cr");
		}
		data->index++;
		i++;
	}
}

void get_index_min_win(t_data *data)
{
  int     rectangle;
  int     len_prompt_cmd;
  int		max_cursor;

	// TODO Functional testing zero division error
	if (isatty(0))
		max_cursor = ((data->len_prompt + (int)ft_strlen(data->cmd)) % data->win_x);
	else
		max_cursor = 0;
  if (max_cursor == 0)
  {
    data->index_min_win = (int)ft_strlen(data->cmd) - (data->win_y * data->win_x);
    return ;
  }
  if ((len_prompt_cmd = (data->len_prompt + (int)ft_strlen(data->cmd))) >= (rectangle = (data->win_x * data->win_y)))
  {
    data->index_min_win = (int)ft_strlen(data->cmd);
    rectangle = rectangle - (data->win_x - (len_prompt_cmd % data->win_x));
    while (rectangle > 0)
    {
      data->index_min_win--;
      rectangle--;
    }
    if (data->index_min_win > data->index)
    {
      data->index = data->index_min_win;
    }
  }
  else
    data->index_min_win = -1;
}

void sigwinch(int sig)
{
  t_data  *data;
	int			old_index;
	int 		old_line_max;
  int     i;

  data = singleton_data(NULL, 0);
  sig = 0;
	(void)sig;
	old_line_max = get_line_max(data);
	(void)old_line_max; // TODO useless set
  get_winsize(data);
  get_index_min_win(data);
	if (((data->len_prompt + (int)ft_strlen(data->cmd)) - (data->win_x)) >= 0)
	{
		// sleep(1);
		// if (data->mode_copy)
		data->mode_copy = 0;
		exec_tcap("cl");
		ft_putstr("\e[38;5;208m");
		ft_putstr(data->prompt);
		ft_putstr("\e[39m");
    if (data->mode_copy)
    {
      i = 0;
      while (data->cmd[i])
      {
        if (i >= data->index_min_copy && i <= data->index_max_copy)
          vi_char(data->cmd[i]);
        else
          ft_putchar(data->cmd[i]);
        i++;
      }
    }
    else
      ft_putstr(data->cmd);
		old_index = data->index;
		data->index = (int)ft_strlen(data->cmd);
		while (old_index < data->index)
			move_left_without_mod(data);
	}
  // if ((int)ft_strlen(data->prompt) + (int)ft_strlen(data->cmd) - data->win_x >= 0) // HOTFIXE CRADE
  // {
  //   // exec_tcap("cl");
  //   // old_index = data->index;
  //   // print_prompt(data->env, data);
  //   // ft_putstr(data->cmd);
  //   // data->index = (int)ft_strlen(data->cmd);
  //   // while (old_index < data->index)
  //   //   move_left(data);
  //   // ret = (int)ft_strlen(data->prompt) + (int)ft_strlen(data->cmd) - data->win_x;
  //   // while (ret >= 0)
  //   // {
  //   //   ret -= data->win_x;
  //   // }
  //   // printf("--------------------------------\n--------------------------------\n--------------------------------\n");
  //   if (data->cmd[data->index] == '\0')
  //     ft_putchar(' ');
  //   else
  //     ft_putchar(data->cmd[data->index]);
  //   data->index++;
  //   move_left(data);
  // }
	// if (data->len_prompt + (int)ft_strlen(data->cmd) > data->win_x)
	// {
	//
	// }
}
