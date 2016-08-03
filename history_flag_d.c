
#include <sh21.h>

void history_flag_d_3(t_data *data, t_history *list)
{
  t_history  *tmp_prec;
  t_history  *tmp_next;

  tmp_prec = list->prec;
  tmp_next = list->next;
  // printf("-------------------------------\n");
  // printf("line prec = [%s]\n", tmp_prec->line);
  // printf("line actual = [%s]\n", list->line);
  // printf("line next = [%s]\n", tmp_next->line);
  if (tmp_prec)
  {
    tmp_prec->next = tmp_next;
    if (tmp_next == NULL)
      data->history = tmp_prec;
  }
  if (tmp_next)
  {
    tmp_next->prec = tmp_prec;
    while (tmp_next->next)
      tmp_next = tmp_next->next;
    data->history = tmp_next;
  }
  if (tmp_prec == NULL && tmp_next == NULL)
    data->history = NULL;
  free(list->line);
  free(list);
  // free(list->line);
  // list->line = ft_strdup("MA BITE EST TRES DURE");
  printf("New end of history = [%s]\n", data->history->line);
}

int  history_flag_d_2(t_data *data, t_history *list, int nb)
{
  int   i;

  i = 1;
  while (i < nb && list != NULL)
  {
    list = list->next;
    i++;
  }
  // printf("SALUT --------\nnb = %d AND list->line = [%s]\n", nb, list->line);
  if (list == NULL || nb == 0)
  {
    ft_putstr_fd("42sh: history: history position out of range\n", 2);
    return (1);
  }
   history_flag_d_3(data, list);
   return (0);
}

int history_flag_d(t_data *data, char **scmd)
{
  t_history     *tmp_deb;
  int           j;

  tmp_deb = data->history;
  while (tmp_deb->prec)
    tmp_deb = tmp_deb->prec;
  j = 0;
  while (scmd[j] != NULL)
  {
    if (ft_isdigit(scmd[j][0]))
    {
      if (history_flag_d_2(data, tmp_deb, ft_atoi(scmd[j])) == 1)
        return (1);
    }
    else
    {
      ft_putstr_fd("42sh: history: Invalid arg, you must specify an positive integer\n", 2);
      return (1);
    }
    j++;
  }
  if (j == 0)
  {
    ft_putstr_fd("42sh: history: Invalid arg, you must specify an positive integer\n", 2);
    return (1);
  }
  return (0);
}
