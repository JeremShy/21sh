/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <vsteffen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:57:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/07/21 23:54:29 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void sigint(int sig)
{
  t_data  *data;

  sig = 0;
  ft_putstr("\n");
  data = singleton_data(NULL, 0);
  data->real_len_cmd = 0;
  data->heredocs = NULL;
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
  if (data->heredocs)
    free_heredoc(data->heredocs);
  if (data->key_here)
    free(data->key_here);
  free(data->command_save);
  data->command_save = ft_strdup("");
  free(data->heredocs_tmp);
  data->heredocs_tmp = ft_strdup("");
  free(data->cmd_tmp);
  data->cmd_tmp = ft_strdup("");
  data->end_hd = 0;
  data->quote_or_hd = 0;
  data->first_line_of_hd = 1;
}

void get_winsize(t_data *data)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  data->win_y = w.ws_row;
  data->win_x = w.ws_col;
	data->after_prompt = (data->len_prompt + 1) % data->win_x;
}

void clear_cmd(t_data	*data)
{
	int	j;
	int	old_index;
	int	i;

	old_index = data->index;
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
	// ft_putstr("\e[38;5;208m");
	// while (i < (int)ft_strlen(data->prompt))
	// {
	// 	ft_putchar(data->prompt[i]);
	// 	if (get_actual_cursor(data) + 1 == data->win_x)
	// 	{
	// 		// exec_tcap("vb");
	// 		exec_tcap("do");
	// 		exec_tcap("cr");
	// 	}
	// 	i++;
	// }
	// ft_putstr("\e[39m");
	// ft_putchar('\n');
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

void sigwinch(int sig)
{
  t_data  *data;
  int     rectangle;

  data = singleton_data(NULL, 0);
  sig = 0;
  get_winsize(data);
  if ((data->len_prompt + (int)ft_strlen(data->cmd)) >= (rectangle = (data->win_x * data->win_y)))
  {
    // exec_tcap("cl");
//  A FAIRE  ------------------>    data->index_min_win = rectangle - (data->win_x * ();
    // ft_putstr(data->cmd + len_cmd - rectangle);
    // printf("strlen = %d /// L AIRE DU CARRE = %d\n", (int)ft_strlen(data->cmd), data->win_y);
    // ft_putstr(data->prompt);
    // ft_putstr(data->cmd);
  }

	// if (i == 0)
	// 	return;
	// i = 0;
	// clear_cmd(data);
	// i = 1;
}
