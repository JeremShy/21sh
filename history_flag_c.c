
#include <sh21.h>


int history_flag_c(t_data *data, t_cmd *cmd)
{
  t_history   *tmp;
  char        *path;

  while (data->history)
  {
      tmp = data->history->prec;
      free(data->history->line);
      free(data->history);
      data->history = tmp;
  }
  path = NULL;
  get_history_path(data, &path);
  if (access(path, F_OK) == 0)
  {
    if (access(path, R_OK) == 0 && access(path, W_OK) == 0)
    {
      data->history_fd = open(path, O_RDWR | O_TRUNC, 0644);
      if (close(data->history_fd) == -1)
      {
        // ft_putstr_fd("42sh: history: Failed to clear history file (close failed)\n", 2);
        // print_prompt(data->env, data);
        return (0);
      }
    }
    else
    {
      // ft_putstr_fd("42sh: history: Failed to clear history file (wrongs permissions)\n", 2);
      // print_prompt(data->env, data);
      return (0);
    }
  }
  return (1);
}
