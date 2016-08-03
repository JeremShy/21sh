
#include <sh21.h>

int history_flag_a(t_data *data)
{
  char			*path;
	int				fd;
	t_history	*history;

	if (get_history_path(data, &path) == 1)
		return (1);
	fd = open(path, O_WRONLY | O_APPEND);
	free(path);
	if (fd == -1 || (history = data->history) == NULL)
		return (1);
	while (history->prec && history->prec->get_from_file == 0)
		history = history->prec;
	while (history)
	{
		path = ft_itoa_base(history->time, 10);
		path = ft_strjoinaf1(path, ";");
		path = ft_strjoinaf1(path, history->line);
		path = ft_strjoinaf1(path, "\n");
		write(fd, path, ft_strlen(path));
		free(path);
    history->get_from_file = 1;
		history = history->next;
	}
	close(fd);
  return (0);
}
