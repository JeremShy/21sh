#include <sh21.h>

void	boucle(t_env *env, t_data *data)
{
	char	buf[11];
	int		r;
	int		flag;

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
		else if (is_boucle_move(data, buf))
		{
		}
		else if (is_boucle_mode_copy(data, buf))
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
		else if (buf[0] == 10 && buf[1] == 0 && !data->mode_copy)
			create_history(data, &env);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0 && !data->mode_copy)
		{
			if (flag == 0)
				flag++;
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
		else if (buf[0] == 9 && buf[1] == 0)
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
