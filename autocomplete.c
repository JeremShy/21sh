#include <sh21.h>

void			ft_autocomplete(t_data *data)
{
	char		*path;
	char		**split;
	char		*ptr;
	char		*prefix;
	char		*ptr_for_chr;
	int			index_to_go;
	char		*tmp;
	t_auto		*next;

	if (is_empty_border_in_actual_cmd(data->cmd, data->index))
		return ;
	if (!data->list_auto)
	{
		data->absolute_index_before_move = data->index;
		while (data->cmd[data->index] && data->cmd[data->index] != ' ')
		{
			move_right_without_mod(data);
		}
		data->index_before_move = data->index;
		if (data->absolute_cmd_before_auto)
			free(data->absolute_cmd_before_auto);
		data->absolute_cmd_before_auto = data->cmd;
		data->cmd = ft_strsub(data->cmd, 0, data->index);
		if (data->absolute_cmd_before_cmd_before_move)
			free(data->absolute_cmd_before_cmd_before_move);
		data->absolute_cmd_before_cmd_before_move = ft_strdup(data->cmd);
		if (is_auto_arg(data->cmd, &ptr, 0, 1))
		{
			data->index_in_word_before_auto = ft_strlen(ptr);
			split = malloc(sizeof(char*) * 2);
			if ((ptr_for_chr = ft_strrchr(ptr, '/')))
			{
				split[0] = ft_strsub(ptr, 0, ptr_for_chr - ptr + 1);
				prefix = ft_strdup(split[0]);
				tmp = ft_strdup(ptr_for_chr + 1);
				free(ptr);
				ptr = tmp;
			}
			else
			{
				prefix = ft_strdup("");
				split[0] = ft_strdup("./");
			}
			split[1] = NULL;
		}
		else if ((ptr_for_chr = ft_strrchr(ptr, '/')))
		{
			split = malloc(sizeof(char*) * 2);
			split[0] = ft_strsub(ptr, 0, ptr_for_chr - ptr + 1);
			split[1] = NULL;
			tmp = ft_strdup(ptr_for_chr + 1);
			free(ptr);
			ptr = tmp;
			prefix = ft_strdup(split[0]);
			data->index_in_word_before_auto = data->index;
		}
		else
		{
			path = find_var_env(data, "PATH", data->env);
			if (ft_strequ(path, ""))
			{
				free(path);
				return ;
			}
			split = ft_strsplit(path, ':');
			free(ptr);
			if (find_ptr(data->cmd) > 0)
				ptr = ft_strdup(find_ptr(data->cmd));
			else
				ptr = ft_strdup(data->cmd);
			prefix = ft_strdup("");
			free(path);
			if (find_ptr(data->cmd) > 0)
				data->index_in_word_before_auto = data->index_before_move - (find_ptr(data->cmd) - data->cmd);
			else
				data->index_in_word_before_auto = 0;
		}
		init_autocomplete(data, split, ptr, prefix);
		free_char_tab(split);
	}
	else if (data->list_auto->next)
	{
		next = data->list_auto->next;
		free(data->list_auto->str);
		free(data->list_auto);
		data->list_auto = next;
	}
	if (!data->list_auto)
	{
		index_to_go = data->absolute_index_before_move;
		while (data->index > 0)
			move_left_without_mod(data);
		ft_putstr(data->absolute_cmd_before_auto);
		free(data->cmd);
		data->cmd = data->absolute_cmd_before_auto;
		data->index = ft_strlen(data->cmd);
		while (data->index > index_to_go)
			move_left_without_mod(data);
		data->cmd_before_auto = NULL;
		data->absolute_cmd_before_auto = NULL;
		data->index_before_auto = 0;
		data->index_before_move = 0;
		return ;
	}
	while (data->index > data->index_before_move)
		move_left_without_mod(data);
	exec_tcap("cd");
	tmp = data->cmd;
	data->cmd = ft_strsub(data->cmd, 0, data->index);
	free(tmp);
	tmp = data->list_auto->str + ft_strlen(find_ptr(data->absolute_cmd_before_cmd_before_move));
	ft_putstr(tmp);
	data->index += ft_strlen(tmp);
	data->cmd = ft_strjoinaf1(data->cmd, tmp);
	tmp = data->absolute_cmd_before_auto + data->index_before_move;
	index_to_go = data->index;
	ft_putstr(tmp);
	data->index += ft_strlen(tmp);
	data->cmd = ft_strjoinaf1(data->cmd, tmp);
	while (data->index > index_to_go)
		move_left_without_mod(data);
}
