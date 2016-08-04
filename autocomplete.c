/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 23:03:00 by JeremShy          #+#    #+#             */
/*   Updated: 2016/08/04 16:24:30 by jcamhi           ###   ########.fr       */
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

static void	init_autocomplete(t_data *data, char **split, char *str_to_equ, char *prefix) // Prends data, un tableau ave les dossiers a parcourir, et le debut de truc a complete, et le prefixe
{
	int		i;
	DIR		*directory;
	t_dirent	*truc;

	i = 0;
	while (split[i])
	{
		directory = opendir(split[i]);
		while (directory && (truc = readdir(directory)))
		{
			if (ft_strnequ(truc->d_name, str_to_equ, ft_strlen(str_to_equ)) && !ft_strequ(truc->d_name, ".") && !ft_strequ(truc->d_name, ".."))
			{
				data->list_auto = add_auto_elem(data->list_auto, create_auto_elem(ft_strjoinaf2(prefix, ft_strdup(truc->d_name))));
				// printf("adding : [%s]\n", truc->d_name);
			}
		}
		if (directory)
			closedir(directory);
		i++;
	}
	free(str_to_equ);
	free(prefix);
}

static int	there_is_a_space(char *cmd, char **ptr) // Note : ptr est la chaine apres l'espace.
{
	size_t	i;

	i = 0;
	*ptr = NULL;
	while (cmd[i])
	{
		if (is_quote_open(cmd[i]))
			get_pos_after_quote(&i, cmd);
		else if (cmd[i] == ' ')
		{
			if (*ptr == NULL)
				*ptr = ft_strdup(cmd + i + 1);
			else
			{
				free(*ptr);
				*ptr = ft_strdup(cmd + i + 1);
			}
			i++;
		}
		else
			i++;
	}
	if (*ptr)
		return (1);
	return (0);
}

void ft_autocomplete(t_data *data)
{
	char	*path;
	char	**split;
	char	*ptr;
	char	*prefix;
	char	*ptr_for_chr;

	if (ft_strequ(data->cmd, ""))
		return ;
	if (!data->list_auto)
	{
		if (there_is_a_space(data->cmd, &ptr))
		{
			data->index_in_word_before_auto = ft_strlen(ptr);
			split = malloc(sizeof(char*) * 2);
			if ((ptr_for_chr = ft_strrchr(ptr, '/')))
			{
					split[0] = ft_strsub(ptr, 0, ptr_for_chr - ptr + 1);
					prefix = ft_strdup(split[0]);
					free(ptr);
					ptr = ft_strdup(ptr_for_chr + 1);
			}
			else
			{
				prefix = ft_strdup("");
				split[0] = ft_strdup("./");
			}
			split[1] = NULL;
		}
		else if ((ptr = ft_strrchr(data->cmd, '/')))
		{
			split = malloc(sizeof(char*) * 2);
			split[0] = ft_strsub(data->cmd, 0, ptr - data->cmd + 1);
			split[1] = NULL;
			// printf("[%s]\n", split[0]);
			ptr = ft_strdup(ptr + 1);
			prefix = ft_strdup(split[0]);
			data->index_in_word_before_auto = data->index;
		}
		else
		{
			path = find_arg(data->env, "PATH");
			if (ft_strequ(path, ""))
			{
				free(path);
				return ;
			}
			split = ft_strsplit(path, ':');
			ptr = ft_strdup(data->cmd);
			prefix = ft_strdup("");
			free(path);
			data->index_in_word_before_auto = data->index;
		}
		init_autocomplete(data, split, ptr, prefix);
	}
	else if (data->list_auto->next)
		data->list_auto = data->list_auto->next;
	if (!data->list_auto)
		return ;
	if (!data->cmd_before_auto)
	{
			data->cmd_before_auto = ft_strdup(data->cmd);
			data->index_before_auto = data->index;
	}
	// printf("%d et %d\n", data->index_in_word_before_auto, data->index_before_auto);
	while (data->index > data->index_before_auto)
		move_left_without_mod(data);
	exec_tcap("cd");
	ft_putstr(data->list_auto->str + data->index_in_word_before_auto);
	free(data->cmd);
	if (data->index_in_word_before_auto != data->index_before_auto)
		data->cmd = ft_strjoin(data->cmd_before_auto, data->list_auto->str + data->index_in_word_before_auto);
	else
		data->cmd = ft_strdup(data->list_auto->str);
	data->index = ft_strlen(data->cmd);
}
