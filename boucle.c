/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:52:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/17 18:42:41 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	check_empty_str(char *s)
{
	int	tmp;

	tmp = 0;
	while(s[tmp])
	{
		if(!ft_isspace2(s[tmp]))
			return(0);
		tmp++;
	}
	return(1);
}

void	after_eof(t_data *data, t_env *env, int *flag)
{
	ft_putstr("\n");
	if (!is_quote_end(data) && data->cmd[0] != '\0' && !check_empty_str(data->cmd)) // Si la quote est terminée..
	{
		*flag = 0;
		data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
		data->history_en_cours = data->history; // On avance dans l'historique
		exec_cmd(data->cmd, &env); // On execute la commande.
	}
	else
	{
		if (data->c == '<')
		{

		}
		else
			data->cmd = ft_strjoinaf1(data->cmd, "\n");
			data->index++;
	}
	free(data->prompt);
	data->prompt = print_prompt(env, data);
	data->len_prompt = ft_strlen(data->prompt) + 1;
	data->real_len_cmd = 0;
	data->curs_x = data->len_prompt + 1;
	data->curs_y = -1;
	if (!(data->c))
	{
		data->cmd = ft_strdup("");
		data->index = 0;
	}
}

void	boucle(t_env *env, t_data *data)
{
	char	buf[6];
	int		r;
	int		flag;
	char	*first;

	flag = 0;
	ft_bzero(buf, 6);
	while ((r = read(0, buf, 5)))
	{
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0')
		{
			data->curs_x++;
			if (data->index == (int)data->real_len_cmd)
			{
				data->cmd = ft_strjoinaf1(data->cmd, buf);
				ft_putchar(buf[0]);
			}
			else
			{
				exec_tcap("im");
				exec_tcap("ic");
				tputs(buf, 1, my_putchar);
				exec_tcap("ei");
				data->cmd = insert_char(data->cmd, data->index, buf[0]);
			}
			data->real_len_cmd++;
			data->index++;
		}
		else if (buf[0] == 4 && buf[1] == 0)
			exit(0);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
				move_left(data);
//			else
//				exec_tcap("bl");
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 )
				move_right(data);
		else if (buf[0] == 127 && buf[1] == 0)
				delete_use(data);
		else if (buf[0] == 10 && buf[1] == 0)
			after_eof(data, env, &flag);
		else if (buf[0] == 27	&&	buf[1] == 91	&&	buf[2] == 72 && buf[3] == 0)
			while (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
				move_left(data);
		else if (buf[0] == 27 && buf[1] == 91	&& buf[2] == 70 && buf[3] == 0)
			while (data->curs_x < data->len_prompt + 1 + (int)data->real_len_cmd)
				move_right(data);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0)
		{
			if (flag == 0)
			{
				flag++;
				first = ft_strdup(data->cmd);
			}
			if (data->history != NULL)
				move_up_history(data, env, first);
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0)
		{
			if (data->history != NULL)
				move_down_history(data, env, first);
		}
		else
		{
			// ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		ft_bzero(buf, 6);
	}
}
