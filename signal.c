/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <vsteffen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:57:58 by vsteffen          #+#    #+#             */
/*   Updated: 2016/07/14 16:53:02 by jcamhi           ###   ########.fr       */
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
  data->curs_y = -1;
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
  data->curs_x = data->len_prompt + 1;
  data->end_hd = 0;
  if (data->heredocs)
    free_heredoc(data->heredocs);
  if (data->key_here)
    free(data->key_here);
}

void get_winsize(t_data *data)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  data->win_y = w.ws_row;
  data->win_x = w.ws_col;
	data->after_prompt = (data->len_prompt + 1) % data->win_x;
}

void sigwinch(int sig)
{
  t_data  *data;

  data = singleton_data(NULL, 0);
  sig = 0;
  get_winsize(data);
}
