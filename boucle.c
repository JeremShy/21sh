#include <sh21.h>

void	boucle(t_env *env, t_data *data)
{
	char	buf[11];
	int		r;
	int		flag;
	char	*first;

	flag = 0;
	ft_bzero(buf, 11);
	if (!isatty(0)) // Pour les tests fonctionnels
	{
		char *str = malloc(1001);
		data->in_env_i = 0;
		if ((r = read(0, str, 1000)))
		{
			str[r] = '\0';
			data->cmd = str;
			create_history(data, &env);
			data->env = env;
			get_index_min_win(data);
			singleton_data(data, 1);
			exit(3);
		}
	}
	while ((r = read(0, buf, 10)))
	{
		data->in_env_i = 0;
		if (is_add_or_del_char(data, buf))
		{
		}
		else if (buf[0] == 4 && buf[1] == 0) // Ctrl + D
		{
			if (data->c == '<')
			{
				reinitialise_heredoc(data, 0);
				create_history(data, &env);
			}
			else if (ft_strequ(data->cmd, ""))
			{
				ft_putstr_fd("exit", 2);
				exit_ctrl_d(env, data);
			}
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
			move_left(data);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && buf[3] == 0)
			move_right(data);
		else if (buf[0] == 10 && buf[1] == 0 && !data->mode_copy)
			create_history(data, &env);
		else if ((buf[0] == 27	&&	buf[1] == 91 && buf[2] == 72 && buf[3] == 0) ||
				(buf[0] == 1 && buf[1] == 0)) // HOME
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (data->mode_copy && data->index == data->index_max_copy)
				data->index_max_copy = data->index_min_copy;
			while(data->index > 0 && data->cmd[data->index - 1] != '\n')
				move_left_without_mod(data);
			if (data->mode_copy)
			{
				data->index_min_copy = data->index;
				while (data->cmd[data->index])
				{
					if (data->index == data->index_min_copy || data->index == data->index_max_copy)
						exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					if (data->index == data->index_max_copy)
						exec_tcap("me");
					data->index++;
				}
				while(data->index > 0 && data->cmd[data->index - 1] != '\n')
					move_left_without_mod(data);
			}
		}
		else if ((buf[0] == 27 && buf[1] == 91	&& buf[2] == 70 && buf[3] == 0) ||
				(buf[0] == 5 && buf[1] == 0)) // END
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (data->mode_copy)
			{
				if (data->index_min_copy == data->index)
					data->index_min_copy = data->index_max_copy;
				data->index_max_copy = (int)ft_strlen(data->cmd) - 1;
				if (data->index > data->index_min_copy)
					exec_tcap("mr");
				while (data->cmd[data->index] && data->cmd[data->index + 1])
				{
					if (data->index == data->index_min_copy)
						exec_tcap("mr");
					ft_putchar(data->cmd[data->index]);
					if (data->index == data->index_max_copy)
						exec_tcap("me");
					data->index++;
				}
				exec_tcap("me");
			}
			else
			{
				ft_putstr(data->cmd + data->index);
				data->index = (int)ft_strlen(data->cmd);
			}
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 53 && buf[3] == 126 && buf[4] == 0) // Page up
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			page_up(data);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 54 && buf[3] == 126 && buf[4] == 0) // Page down
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			page_down(data);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0 && !data->mode_copy)
		{
			if (flag == 0)
			{
				flag++;
				first = ft_strdup(data->cmd);
				(void)first; // TODO
			}
			move_up_history(data, env);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0 && !data->mode_copy)
			move_down_history(data, env);
		else if (buf[0] == 16 && buf[1] == 0 && !data->mode_copy)
		{
			char *pb = get_pb();
			data->real_len_cmd += ft_strlen(pb);
			data->index += ft_strlen(pb);
			ft_putstr(pb);
			data->cmd = ft_strjoinaf12(data->cmd, pb);
		}
		else if (buf[0] == 12 && buf[1] == 0  && buf[2] == 0 && !data->mode_copy) // CTRL + L
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			exec_tcap("cl");
			ft_putstr("\e[38;5;208m");
			ft_putstr(data->prompt);
			ft_putstr("\e[39m");
			ft_putstr(data->cmd);
			int ind_act = ft_strlen(data->cmd);
			while (ind_act > data->index)
			{
				exec_tcap("le");
				ind_act--;
			}
		}
		else if (buf[0] == -62 && buf[1] == -75 && buf[2] == 0) // MODE COPY
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (data->mode_copy == 0 && data->cmd[0] != '\0' && data->index != (int)ft_strlen(data->cmd))
			{
				int	origin;

				data->index_min_copy = data->index;
				data->index_max_copy = data->index;
				origin = data->index;
				vi_char(data->cmd[data->index]);
				data->index++;
				while (data->cmd[data->index])
				{
					ft_putchar(data->cmd[data->index]);
					data->index++;
				}
				while (data->index > origin)
					move_left(data);
				data->mode_copy = 1;
			}
			else
			{
				int	origin = data->index;

				data->mode_copy = 0;
				while (data->index > 0 && data->cmd[data->index - 1] != '\n')
				{
					move_left_without_mod(data);
				}
				ft_putstr(data->cmd + data->index);
				data->index = (int)ft_strlen(data->cmd);
				while (data->index > origin)
					move_left_without_mod(data);
			}
		}
		else if (buf[0] == -61 && buf[1] == -89 && buf[2] == 0) // copie
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			int	index_origine;
			if (data->mode_copy)
			{
				data->mode_copy = 0;
				index_origine = data->index;
				while (data->index > data->index_min_copy)
					move_left(data);
				while (data->index <= data->index_max_copy)
				{
					ft_putchar(data->cmd[data->index]);
					data->index++;
				}
				while (data->index > index_origine)
					move_left(data);
				if (data->clipboard)
					free(data->clipboard);
				data->clipboard = ft_strsub(data->cmd, data->index_min_copy, data->index_max_copy - data->index_min_copy + 1);
			}
		}
		else if (buf[0] == -30 && buf[1] == -119 && buf[2] == -120 && buf[3] == 0) // cut
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (data->mode_copy)
			{
				data->mode_copy = 0;
				if (data->clipboard)
					free(data->clipboard);
				data->clipboard = ft_strsub(data->cmd, data->index_min_copy, data->index_max_copy - data->index_min_copy + 1);
				while (data->index <= data->index_max_copy)
					move_right_without_mod(data);
				while (data->index > data->index_min_copy)
					delete_mode(data);
			}
		}
		else if (buf[0] == -30 && buf[1] == -120 && buf[2] == -102 && buf[3] == 0) // paste
		{
			int	i;

			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (!data->mode_copy)
			{
				if (data->clipboard)
				{
					i = 0;
					while (data->clipboard[i])
					{
						insert_mode(data, data->clipboard[i]);
						i++;
					}
				}
			}
		}
		else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 68 && buf[4] == 0) // Previous word
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			previous_word(data);
		}
		else if (buf[0] == 27 && buf[1] == 27 && buf[2] == 91 && buf[3] == 67 && buf[4] == 0) // Next Word
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			next_word(data);
		}
		else if (buf[0] == 27 && buf[1] == 0) // AFFICHE MESSAGE DE DEBUG 1
		{
			// printf("index - %d AND index_min_copy = %d AND index_max_copy = %d\n", data->index, data->index_min_copy, data->index_max_copy);
		}
		else if (buf[0] == 29 && buf[1] == 0) // AFFICHE MESSAGE DE DEBUG 2
		{
			printf ("DEBUG --> data->cmd = [%s] AND .. [%s]\n", data->cmd, data->cmd + 10);
		}
		else if (buf[0] == 9 && buf[1] == 0) // Autocompletion
		{
			if (!data->c && !data->mode_copy)
			{
				ft_autocomplete(data);
			}
		}
		else
		{
		}
		data->env = env;
		get_index_min_win(data);
		singleton_data(data, 1);
		ft_bzero(buf, 11);
	}
}
