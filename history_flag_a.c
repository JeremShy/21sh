
#include <sh21.h>

int		get_history_path_anrw(t_data *data, char **path, char *scmd)
{
	char	*history_name;

	*path = find_var_env(data, "HOME");
	if (*path[0] == '\0')
	{
		free(*path);
		return (1);
	}
	else
	{
    history_name = find_var_env(data, "HISTFILE");
    if (scmd != NULL)
    {
      *path = ft_strjoinaf1(*path, "/");
      *path = ft_strjoinaf1(*path, scmd);
    }
    else if (history_name[0] == '\0')
      *path = ft_strjoinaf1(*path, "/42sh_history");
    else
    {
      *path = ft_strjoinaf1(*path, "/");
      *path = ft_strjoinaf1(*path, history_name);
    }
    free(history_name);
	}
	return (0);
}

int history_flag_a(t_data *data, char *scmd)
{
  char			*path;
	int				fd;
	t_history	*history;

	if (get_history_path_anrw(data, &path, scmd) == 1)
		return (1);
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0600);
	free(path);
	if (fd == -1 || (history = data->history) == NULL)
		return (1);
	while (history->prec && history->prec->get_from_file == 0)
		history = history->prec;
	if (history->get_from_file == 1)
		return (1);
	while (history)
	{
		path = ft_itoa_base(history->time, 10);
		path = ft_strjoinaf1(path, ";");
		path = ft_strjoinaf1(path, history->line);
		path = ft_strjoinaf1(path, "\n");
		write(fd, path, ft_strlen(path));
		free(path);
		history = history->next;
	}
	close(fd);
  return (0);
}
