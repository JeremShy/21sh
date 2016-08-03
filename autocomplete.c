/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 23:03:00 by JeremShy          #+#    #+#             */
/*   Updated: 2016/08/03 23:42:00 by JeremShy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

t_auto *create_auto_elem (char *content)
{
	t_auto	*elem;

	elem = malloc(sizeof(t_auto));
	elem->str = content;
	elem->next = NULL;
	return (elem);
}

t_auto 	*add_auto_elem(t_auto *list, t_auto *elem)
{
	t_auto *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
  		list = list->next;
	list->next = elem;
	return (tmp);
}

static void	init_autocomplete(t_data *data)
{
	char	*path;
	char	**split;
	int		i;
	DIR		*directory;
	t_dirent	*truc;

	path = find_arg(data->env, "PATH");
	if (ft_strequ(path, ""))
	{
		free(path);
		return ;
	}
	split = ft_strsplit(path, ':');
	free(path);
	i = 0;
	while (split[i])
	{
		directory = opendir(split[i]);
		while (directory && (truc = readdir(directory)))
		{
			if (ft_strnequ(truc->d_name, data->cmd, ft_strlen(data->cmd)) && !ft_strequ(truc->d_name, ".") && !ft_strequ(truc->d_name, ".."))
			{
				data->list_auto = add_auto_elem(data->list_auto, create_auto_elem(ft_strdup(truc->d_name)));
			}
		}
		if (directory)
			closedir(directory);
		i++;
	}
}

void ft_autocomplete(t_data *data)
{
	if (!data->list_auto)
	{
		init_autocomplete(data);
	}
	else if (data->list_auto->next)
	{
		data->list_auto = data->list_auto->next;
	}
	if (!data->list_auto)
		return ;
	if (!data->cmd_before_auto)
			data->cmd_before_auto = ft_strdup(data->cmd);
	while (data->index > 0)
		move_left_without_mod(data);
	exec_tcap("cd");
	ft_putstr(data->list_auto->str);
	free(data->cmd);
	data->cmd = ft_strdup(data->list_auto->str);
	data->index = ft_strlen(data->cmd);
}
