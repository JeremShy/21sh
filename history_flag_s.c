
#include <sh21.h>

void delete_last_history(t_data *data)
{
  t_history *list;

  list = data->history;
  if (list)
  {
    if (list->prec)
    {
      data->history = list->prec;
      data->history->next = NULL;
    }
    else
      data->history = NULL;
    free(list->line);
    free(list);
  }
}

char		*history_subsitution_nb_arg(t_data *data, char *command)
{
	int				nb;
	t_history	*list;
	int				i;

	if ((nb = ft_atoi(command)) == 0)
		return (NULL);
	if ((list = data->history) == NULL)
		return (NULL);
	while (list->prec)
		list = list->prec;
	i = 1;
	while (list->next && nb > i)
	{
		i++;
		list = list->next;
	}
	if (nb == i)
		return (ft_strdup(list->line));
	ft_putstr_fd("42sh: history position out of range\n", 2);
	return (NULL);
}

// char  *get_history_substutition(t_data *data, char *scmd)
// {
//   char      *str;
//   t_history *list;
//   int       len;
//
//   str = NULL;
//   // printf("actual history = [%s]\n", data->history->line);
//   if (scmd[0] == '!' && scmd[1] == '\0')
//   {
//     if (data->history != NULL)
//     {
//       data->history = add_history_elem(data->history, create_history_elem(data->cmd));
//       return (ft_strdup(data->history->line));
//     }
//     return (NULL);
//   }
//   else if (ft_isdigit(scmd[0]))
//   {
//     if ((str = history_subsitution_nb_arg_ps(data, scmd)))
//       return (str);
//     return (NULL);
//   }
//   str = NULL;
//   list = data->history;
//   len = (int)ft_strlen(scmd);
//   printf("JE PASSE ICI ! \n");
//   while (list)
//   {
//     if (ft_strnequ(scmd, list->line, len))
//       return (ft_strdup(list->line));
//     list = list->prec;
//   }
//   return (str);
// }

int history_flag_s(t_data *data, char **scmd)
{
  int   j;

  j = 0;
  while (scmd[j] != NULL)
  {
    data->history = add_history_elem(data->history, create_history_elem(ft_strdup(scmd[j])));
    j++;
  }
  return (0);
}
