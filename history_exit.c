/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:30:25 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 17:30:32 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	history_exit(t_data *data)
{
	char		*path;
	int			fd;
	t_history	*history;

	if (get_history_path(data, &path) == 1)
		return ;
	fd = open(path, O_RDWR | O_CREAT | O_APPEND, 0600);
	free(path);
	if (fd == -1 || (history = data->history) == NULL)
		return ;
	while (history->prec && history->prec->get_from_file == 0)
		history = history->prec;
	if (history->get_from_file == 1)
		return ;
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
}
