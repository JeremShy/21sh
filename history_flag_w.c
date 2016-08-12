
#include <sh21.h>

int history_flag_w(t_data *data, char *scmd, t_cmd *cmd)
{
  char			*path;
	t_history	*history;

	if (get_history_path_anrw(data, &path, scmd) == 1)
		return (1);
	data->history_fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	free(path);
	if (data->history_fd == -1 || (history = data->history) == NULL)
		return (1);
	while (history->prec)
		history = history->prec;
	while (history)
	{
		path = ft_itoa_base(history->time, 10);
		path = ft_strjoinaf1(path, ";");
		path = ft_strjoinaf1(path, history->line);
		path = ft_strjoinaf1(path, "\n");
		write(data->history_fd, path, ft_strlen(path));
		free(path);
		history = history->next;
	}
	close(data->history_fd);
  return (0);
}
