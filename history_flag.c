
#include <sh21.h>

void print_numero_and_time(t_data *data, char *line, int j)
{
  char      *arg;
  int       strtime;
  int       i;
  // time_t  timecaster;
  //
  // timecaster = (time_t)ft_atoi(line);
  // printf("time = %ld\n", timecaster);
  // if (timecaster != 0)
  // {
  //   strtime = ctime(&timecaster);
  //   ft_putstr(strtime);
  //   ft_putchar(' ');
  // }
  // *i += (int)ft_strlen(strtime);
  arg = find_arg(data->env, "HISTTIMEFORMAT");
  ft_putnbr(j);
  if (arg[0] == '1' && arg[1] == '\0')
  {
    ft_putchar(' ');
    strtime = ft_atoi(line);
    i = 0;
    if (strtime != 0)
      ft_putnbr(strtime);
    else
      ft_putstr("[NO TIMESTAMP]");
  }
  free(arg);
  ft_putchar(' ');
}

int history_flag_none(t_data *data)
{
  char		*line;
  size_t  i;
  size_t  j;

  if (get_history_fd(data) == 1 && data->history_fd == -1)
    return (0);
  j = 1;
  line = NULL;
  while (get_next_line(data->history_fd, &line) == 1)
  {
    i = 0;
    print_numero_and_time(data, line, j);
    while (line[i] != ';' && line[i])
      i++;
    if (line[i])
      i++;
    ft_putstr(line + i);
    ft_putchar('\n');
    j++;
    free(line);
  }
  if (close(data->history_fd) == -1)
		ft_putstr_fd("42sh: history: Failed to open/close history file\n", 2);
  data = NULL;
  return (0);
}

int history_flag_c(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_d(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_a(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_w(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_r(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_n(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_p(t_data *data)
{
  data = NULL;
  return (0);
}

int history_flag_s(t_data *data)
{
  data = NULL;
  return (0);
}
