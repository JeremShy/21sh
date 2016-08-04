
#include <sh21.h>

void delete_last_history(t_data *data)
{
  t_history *list;

  list = data->history->prec;
  if (list)
  {
    free(data->history->line);
    free(data->history);
    list->next = NULL;
    data->history = list;
  }
}

// t_history   *get_history_line_substitution(t_data *data, int arg)
// {
//   t_history   *tmp;
//
//   if (arg == 0)
//     list = NULL;
//   else
//   {
//     while (list->prec && *i < arg)
//     {
//       (*i)++;
//       list = list->prec;
//     }
//     *i = 1;
//     tmp = list;
//     while (tmp->prec)
//     {
//       tmp = tmp->prec;
//       (*i)++;
//     }
//   }
//   return (list);
// }

char  *get_history_substutition(t_data *data, char *scmd)
{
  char      *str;
  t_history *list;
  int       len;
  // int       nb;

  str = NULL;
  list = data->history;
  len = (int)ft_strlen(scmd);
  // nb = ft_atoi(scmd);
  // if (nb > 0)
  //   return (subs_nb_command(data, scmd));
  // else
  // {
    while (list)
    {
      if (ft_strnequ(scmd, list->line, len))
        return (ft_strdup(list->line));
      list = list->prec;
    }
  // }
  return (str);
}

int history_flag_s(t_data *data, char **scmd)
{
  int   j;
  char  *arg;

  if (scmd[0] == NULL)
    return (0);
  else
  {
    delete_last_history(data);
    j = 0;
    while (scmd[j] != NULL)
    {
      if (scmd[j][0] == '!')
      {
        if ((arg = get_history_substutition(data, scmd[j] + 1)) == NULL)
        {
          ft_putstr_fd("42sh: history: command not found\n", 2);
          return (1);
        }
      }
      else
        arg = scmd[j];
      data->history = add_history_elem(data->history, create_history_elem(ft_strdup(arg)));
      j++;
    }
  }
  return (0);
}
