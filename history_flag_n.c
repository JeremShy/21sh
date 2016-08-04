
#include <sh21.h>

int   get_current_time(void)
{
  struct timeval 	tv;

  gettimeofday(&tv, NULL);
  return ((int)tv.tv_sec);
}

int history_flag_n(t_data *data, char *scmd)
{
  char			*path;
	t_history	*history;
  int       time_line;
  char      *command_line;
  char      *line;

	if (get_history_path_anrw(data, &path, scmd) == 1)
		return (1);
    // printf("IN FLAG R\n");
  	data->history_fd = open(path, O_RDONLY);
    free(path);
    if (data->history_fd == -1 || data->history == NULL)
      return (1);
    line  = NULL;
  	while (get_next_line(data->history_fd, &line) == 1)
  	{
      time_line = ft_atoi(line);
      command_line = line + get_history_command_part(line);
      history = data->history;
      while (history->prec && time_line < history->time && ft_strequ(history->line, command_line) == 0)
        history = history->prec;
      if (ft_strequ(history->line, command_line) == 0)
      {
          printf("-----------  COMMAND FOUND = [%s]\n", command_line);
  		    data->history = add_history_elem(data->history, create_history_elem(ft_strdup(command_line)));
  		    data->history->time = ft_atoi(line);// HOTFIXE DEGUEULASSE CAR FLEMME DE CHANGER LES HEADERS POUR RAJOUTER LE TIME DU FICHIER
      }
      free(line);
  	}
  	if (close(data->history_fd) == -1)
  		ft_putstr_fd("42sh: history: Failed to open/close history file\n", 2);
    return (0);
}
