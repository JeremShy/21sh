/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 12:51:49 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/03 20:11:59 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_history	*create_history_elem(char *content)
{
	static int	i = 1;
	t_history		*elem;

	elem = (t_history*)malloc(sizeof(t_history));
	elem->line = ft_strdup(content);
	elem->index = i;
	elem->next = NULL;
	elem->prec = NULL;
	i++;
	return (elem);
}

t_history *add_history_elem(t_history *list, t_history *elem)
{
	if (list == NULL)
		return (elem);
	list->next = elem;
	elem->prec = list;
	return (elem);
}

int		get_history_path(t_data *data, char **path)
{
	char	*history_name;

	*path = find_arg(data->env, "HOME");
	if (*path[0] == '\0')
	{
		printf("42sh: history: $HOME isn't set, impossible to create or read history file\n");
		free(*path);
		return (1);
	}
	else
	{
		history_name = find_arg(data->env, "HISTFILE");
		if (history_name[0] == '\0')
		{
			free(history_name);
			*path = ft_strjoinaf1(*path, "/42sh_history");
		}
		else
		{
			*path = ft_strjoinaf1(*path, "/");
			*path = ft_strjoinaf12(*path, history_name);
		}
	}
	// printf("path = [%s]\n", *path);
	return (0);
}

int get_history_fd(t_data *data)
{
	char	*path;

	path = NULL;
	data->history_fd = -1;
	if (get_history_path(data, &path) == 1)
		return (1);
	if (access(path, F_OK) == -1)
	{
		data->history_fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (access(path, R_OK) == 0)
	{
		data->history_fd = open(path, O_RDONLY);
	}
	else
		ft_putstr_fd("42sh: history: Failed to read history file\n", 2);
	free(path);
	return (0);
}

void init_history(t_data *data)
{
	char		*line;

	line = NULL;
	if (get_history_fd(data) == 1 && data->history_fd == -1)
		return ;
	while (get_next_line(data->history_fd, &line) == 1)
	{
		data->history = add_history_elem(data->history, create_history_elem(line));
	}
	if (close(data->history_fd) == -1)
		ft_putstr_fd("42sh: history: Failed to open/close history file\n", 2);
}
