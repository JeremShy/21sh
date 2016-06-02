/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:52:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/01 18:27:11 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	prompt_quote(t_data *data)
{
	data->prompt = NULL;
	if (data->c == '\'')
		data->prompt = ft_strdup("quote> ");
	else if (data->c == '"')
		data->prompt = ft_strdup("dquote> ");
	else if (data->c == '`')
		data->prompt = ft_strdup("bquote> ");
	else if (data->c == '(')
		data->prompt = ft_strdup("parenthese> ");
	else if (data->c == '[')
		data->prompt = ft_strdup("crochet> ");
	else if (data->c == '{')
		data->prompt = ft_strdup("cursh> ");
	ft_putstr(data->prompt);
}

void	boucle(t_env *env, t_data *data)
{
	char	buf[6];
	int		r;

	ft_bzero(buf, 6);
	while ((r = read(0, buf, 5)))
	{
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) || (buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) && buf[1] == '\0')
		{
			data->curs_x++;
			if (data->index == (int)ft_strlen(data->cmd))
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
			data->index++;
		}
		else if (buf[0] == 4 && buf[1] == 0)
			exit(0);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
		{
			if (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
				move_left(data);
//			else
//				exec_tcap("bl");
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 )
		{
			if (data->curs_x < data->len_prompt +
				1 + (int)ft_strlen(data->cmd))
				move_right(data);
		}
		else if (buf[0] == 127 && buf[1] == 0)
		{
			if (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
			{
				exec_tcap("le");
				data->curs_x--;
				data->cmd = delete_char(data->cmd, data->index);
				data->index--;
				exec_tcap("dm");
				exec_tcap("dc");
				exec_tcap("ed");
			}
		}
		else if (buf[0] == 10 && buf[1] == 0)
		{
			ft_putstr("\n");
			if (!is_quote_end(data))
				exec_cmd(data->cmd, &env);
			else
				data->cmd = ft_strjoinaf1(data->cmd, "\n");
			free(data->prompt);
			data->prompt = print_prompt(env, data);
			data->len_prompt = ft_strlen(data->prompt);
			data->curs_x = data->len_prompt + 1;
			data->curs_y = -1;
			if (!(data->c))
				data->cmd = ft_strdup("");
			data->index = 0;
		}
		else if (buf[0] == 27	&&	buf[1] == 91	&&	buf[2] == 72 && buf[3] == 0)
			while(data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
				move_left(data);
		else if (buf[0] == 27 && buf[1] == 91	&& buf[2] == 70 && buf[3] == 0)
		{
			while(data->curs_x < data->len_prompt + 1 + (int)ft_strlen(data->cmd))
			{
				move_right(data);
			}
		}
		else
		{
	//		ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		ft_bzero(buf, 6);
	}
}
