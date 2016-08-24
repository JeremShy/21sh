#include <sh21.h>

void	prompt_quote(t_data *data)
{
	if (data->c == '\'')
		data->prompt = ft_strdup("quote> ");
	else if (data->c == '"')
		data->prompt = ft_strdup("dquote> ");
	else if (data->c == '`')
		data->prompt = ft_strdup("bquote> ");
	else if (data->c == '(')
		data->prompt = ft_strdup("subsh> ");
	else if (data->c == '[')
		data->prompt = ft_strdup("crochet> ");
	else if (data->c == '{')
		data->prompt = ft_strdup("cursh> ");
	else if (data->c == '<')
		data->prompt = ft_strdup("heredoc> ");
	ft_putstr(data->prompt);
	// printf("------- data->cmd = [%s]\n", data->cmd);
}

void	move_up_history(t_data *data, t_env *env)
{
	t_history	*temp;

	if (data->c == '\0' && data->history != NULL)
	{
		if (!data->first && data->first_search) // Si c'est la premiere fois qu'on appuie sur haut..
		{
			data->first_search = 0; // On change le fait que c'est la premiere fois
			if (!ft_strequ(data->cmd, "")) // Et si y a qqc dans notre commande, on s'en sert pour notre recherche future.
				data->first = ft_strdup(data->cmd);
		}
		if (!data->first && data->history_en_cours == NULL) //Si on est sorti de l'historique et qu'on a pas de recherche a faire, on part du depart (empeche de sauter le 1er element)
			data->history_en_cours = data->history;
		else if (data->first) // Sinon si on a une recherche a faire..
		{
			temp = data->history_en_cours; // On sauvegarde l'historique, au cas où on doive sortir plus tard
			if (!data->history_en_cours) // Si on est sorti, on part du premier
				data->history_en_cours = data->history;
			else if (data->history_en_cours->prec) // Sinon on part de celui d'avant(pour eviter de stagner sur le meme element)
				data->history_en_cours = data->history_en_cours->prec;
			while(!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first)) //Tant que celui sur lequel on est ne correspond pas à notre recherche, et qu'il y en a un avant..
				&& data->history_en_cours->prec)
			{
				data->history_en_cours = data->history_en_cours->prec; // On recule dans notre historique
			}
			if (!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first))) // Si on s'est pas arrete parce que le truc correspond, alors c'est qu'on s'est arrete parce qu'on etait a la fin. auquel cas, on fait comme si on avait rien fait.
			{
				data->history_en_cours = temp;
				return ;
			}
		}
		else
		{
			if (data->history_en_cours->prec)
				data->history_en_cours = data->history_en_cours->prec;
			else
				return ;
		}
		exec_tcap("dl");
		exec_tcap("cr");
		free(data->prompt);
		data->prompt = print_prompt(env, data);
		data->len_prompt = ft_strlen(data->prompt);
		ft_putstr((data->history_en_cours)->line);
		if (data->cmd)
			free(data->cmd);
		data->cmd = ft_strdup((data->history_en_cours)->line);
		data->real_len_cmd = ft_strlen(data->cmd);
		data->index = ft_strlen(data->cmd);
		data->curs_x = data->len_prompt + data->real_len_cmd + 1;
		if (data->list_auto)
		{
			delete_list_auto(data->list_auto);
			data->list_auto = NULL;
		}
	}
	else
	{
		//On fait des trucs. (important).
	}
}

void	move_down_history(t_data *data, t_env *env)
{
	if (data->c == '\0')
	{
		if (data->history != NULL)
		{
			if (data->history_en_cours == NULL)
			{
				return ;
			}
			if (data->cmd)
				free(data->cmd);
			if (data->first)
			{
				data->history_en_cours = data->history_en_cours->next;
				while (data->history_en_cours &&
					!ft_strnequ(data->history_en_cours->line, data->first, ft_strlen(data->first)))
				{
					data->history_en_cours = data->history_en_cours->next;
				}
				if (!data->history_en_cours)
				{
					data->cmd = ft_strdup(data->first);
				}
				else
					data->cmd = ft_strdup(data->history_en_cours->line);
			}
			else if ((data->history_en_cours)->next)
			{
				data->history_en_cours = (data->history_en_cours)->next;
				data->cmd = ft_strdup(data->history_en_cours->line);
			}
			else
			{
				data->history_en_cours = NULL;
				// data->cmd = old_cmd;
				data->cmd = ft_strdup("");
				// return ;
			}
			exec_tcap("dl");
			exec_tcap("cr");
			free(data->prompt);
			data->prompt = print_prompt(env, data);
			data->len_prompt = ft_strlen(data->prompt);
			ft_putstr(data->cmd);
			data->real_len_cmd = ft_strlen(data->cmd);
			data->index = ft_strlen(data->cmd);
			data->curs_x = data->len_prompt + data->real_len_cmd + 1;
			data->curs_y = 0;
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
		}
	}
}

int	create_history(t_data *data, t_env **env)
{
	int i;

	i = 0;
	// printf("DATA->INDEX = %d\n", data->index);
	// printf("CURSEUR = [%d] /// INDEX  = [%d] /// DATA->WIN_X = [%d]\n", get_actual_cursor(data), data->index, data->win_x);
	ft_putstr("\n");
	// if (data->cmd[0] == '!')
	// 	if (get_history_substutition_for_boucle(data, data->cmd + 1) == 0)
	// 		return (0);
	if (true_var_and_subs(data, &data->cmd) && data->c != '<' && (i = is_quote_end(data)) == 0 && (data->cmd[0] != '\0')) // Si la quote est terminée...
	{
		if (data->cmd_tmp[0] == '\0')
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
		}
		else
		{
			if (data->quote_or_hd == 0) // Il ne faut pas joindre les heredocs à la commande.
				data->cmd = ft_strjoinaf2(data->cmd_tmp, data->cmd);
		}
		// data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
		// printf("\nexecuting command now...\n");
		data->index = 0;
		invert_term();
		signal(SIGINT, SIG_IGN);
		exec_cmd(env, parse(data->cmd, data->heredocs, env, data), data); // On execute la commande.
		signal(SIGINT, sigint);
		invert_term();
		// printf("\nthe command has been executed\n");
		// display_heredoc(data->heredocs);
		data->c = '\0';
		//-------------------------
		reinitialise_heredoc(data, 1);
		if (data->cmd_tmp)
			free(data->cmd_tmp);
		data->cmd_tmp = ft_strdup("");
		data->quote_old_index = 0;
		if (data->list_auto)
		{
			delete_list_auto(data->list_auto);
			data->list_auto = NULL;
		}
		delete_list_command(data->command);
				data->command = NULL;
	}
	else
	{
		if (i == -1)
		{
			reinitialise_heredoc(data, 1);
		}
		else if (data->c == '<')
		{
			if (is_key(data))
			{
				reinitialise_heredoc(data, 0);
				return (create_history(data, env));
			}
			else
			{
				if (data->first_line_of_hd == 0)
				{
					data->heredocs_tmp = ft_strjoinaf1(data->heredocs_tmp, data->cmd);
					data->heredocs_tmp = ft_strjoinaf1(data->heredocs_tmp, "\n");
				}
				data->first_line_of_hd = 0;
			}
		}
		else if (data->c == '\0')
		{
			free(data->cmd_tmp);
			data->cmd_tmp = ft_strdup("");
		}
		else
		{
			data->cmd_tmp = ft_strjoinaf1(data->cmd_tmp, data->cmd);
			data->cmd_tmp = ft_strjoinaf1(data->cmd_tmp, "\n");
		}
		data->index++;
	}
	free(data->prompt);
	data->prompt = print_prompt(*env, data);
	data->len_prompt = ft_strlen(data->prompt);
	data->real_len_cmd = 0;
	data->curs_x = data->len_prompt + 1;
	data->curs_y = -1;
	if (data->first)
	{
		free(data->first);
		data->first = NULL;
	}
	data->first_search = 1;
	data->history_en_cours = NULL;
	if (data->cmd)
		free(data->cmd);
	data->cmd = ft_strdup("");
	data->index = 0;
	return (0);
}

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
		char str[101];
		data->in_env_i = 0;
		if ((r = read(0, str, 100)))
		{
			str[r] = '\0';
			data->cmd = str;
			//printf ("str : [%s]\n", str);
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
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0' && !data->mode_copy)
		{
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			data->curs_x++;
			if (data->index == (int)data->real_len_cmd)
			{
				data->cmd = ft_strjoinaf1(data->cmd, buf);
				ft_putchar(buf[0]);
				data->index++;
			}
			else
			{
				insert_mode(data, buf[0]);
			}
			data->real_len_cmd++;
			data->first_search = 1;
			if (data->first)
			{
				free(data->first);
				data->first = NULL;
			}
		}
		else if (buf[0] == 4 && buf[1] == 0) // Ctrl + D
		// FREE DATA;
		{
			if (data->c == '<')
			{
				reinitialise_heredoc(data, 0);
				create_history(data, &env);
				// create_history(data, env);
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
		else if (buf[0] == 127 && buf[1] == 0 && !data->mode_copy)
		{
			//TODO free list_auto
			if (data->list_auto)
			{
				delete_list_auto(data->list_auto);
				data->list_auto = NULL;
			}
			if (data->index > 0)
			{
				delete_mode(data);
				data->first_search = 1;
				if (data->first)
				{
					free(data->first);
					data->first = NULL;
				}
				if (ft_strequ(data->cmd, ""))
					data->history_en_cours = NULL; // Voir si on veut le mettre
			}
		}
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
			data->curs_x += ft_strlen(pb);
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
				// ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		data->env = env;
		get_index_min_win(data);
		singleton_data(data, 1);
		ft_bzero(buf, 11);
	}
}
