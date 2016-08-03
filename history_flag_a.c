
#include <sh21.h>

int history_flag_a(t_data *data)
{
  char  *path;

  path = NULL;
  if (get_history_path(data, &path) == 1)
    return (1);
  if ((data->history_fd = open(path, O_RDWR | O_APPEND, 0600)) == -1)
  {
    ft_putstr_fd("42sh: history: Failed to append history session on history file\n", 2);
    free(path);
    return (1);
  }
  free(path);
  return (0);
}
