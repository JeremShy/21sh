/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boucle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 19:52:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/04 11:52:54 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	check_empty_str(char *s)
{
	int	tmp;

	// if (data->c == '\'')
	// 	data->prompt = ft_strdup("quote> ");
	// else if (data->c == '"')
	// 	data->prompt = ft_strdup("dquote> ");
	// else if (data->c == '`')
	// 	data->prompt = ft_strdup("bquote> ");
	// else if (data->c == '(')
	// 	data->prompt = ft_strdup("subsh> ");
	// else if (data->c == '[')
	// 	data->prompt = ft_strdup("crochet> ");
	// else if (data->c == '{')
	// 	data->prompt = ft_strdup("cursh> ");
	// else if (data->c == '<')
	// 	data->prompt = ft_strdup("heredoc> ");
	// ft_putstr(data->prompt);
	// printf("------- data->cmd = [%s]\n", data->cmd);
// }
	tmp = 0;
	while(s[tmp])
	{
		if(!ft_isspace2(s[tmp]))
			return(0);
		tmp++;
	}
	return(1);
}

// void	move_down_history(t_data *data, t_env *env)
// {
// 	if (data->c == '\0')
// 	{
// 		if (data->history != NULL)
// 		{
// 			exec_tcap("dl");
// 			exec_tcap("cr");
// 			data->prompt = print_prompt(env, data);
// 			data->len_prompt = ft_strlen(data->prompt);
// 			if (data->history_en_cours == NULL)
// 				data->history_en_cours = data->history;
// 			if (!(data->history_en_cours)->next)
// 			{
// 				data->cmd = ft_strdup("");
// 				data->real_len_cmd = 0;
// 				data->index = 0;
// 				data->curs_x = data->len_prompt + data->real_len_cmd;
// 				return ;
// 			}
// 			free(data->cmd);
// 			if ((data->history_en_cours)->next)
// 				data->history_en_cours = (data->history_en_cours)->next;
// 			ft_putstr((data->history_en_cours)->line);
// 			data->cmd = ft_strdup((data->history_en_cours)->line);
// 			data->real_len_cmd = ft_strlen(data->cmd);
// 			data->index = ft_strlen(data->cmd);
// 			data->curs_x = data->len_prompt + data->real_len_cmd;
// 		}
// 	}
// }

int	create_history(t_data *data, t_env *env)
{
	int i;

	i = 0;
	ft_putstr("\n");
	if (!is_quote_end(data) && !check_empty_str(data->cmd)) // Si la quote est terminée..
	{
		data->flag = 0;
		data->first = ft_strdup("");
		data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
		data->history_en_cours = NULL;
		exec_cmd(data, &env); // On execute la commande.
	}
	// else
	// {
	// 	data->history_en_cours = data->history; // On avance dans l'historique
	// 	printf("\nexecuting command now...\n");
	// 	exec_cmd(data, &env); // On execute la commande.
	// 	printf("\nthe command has been executed\n");
	// 	display_heredoc(data->heredocs);
	// 	data->c = '\0';
	// 	data->end_hd = 0;
	// 	free_heredoc(data->heredocs);
	// 	data->heredocs = NULL;
	// }
	else
	{
		if (i == -1)
		{
			//Parse error
			data->c = '\0'; // Pour tout reinitialiser par la suite.
			//FREE HEREDOCS
			free_heredoc(data->heredocs);
			data->heredocs = NULL;
			free(data->cmd);
		}
		else if (data->c == '<')
		{
			printf("--------  data->cmd : %s\n", data->cmd);
			if (is_key(data))
			{
				// printf("on ajoute [%s]\n", data->cmd + 1);
				data->heredocs = add_hc_elem(data->heredocs, create_hc_elem(data->cmd + 1));
				data->cmd = data->ancienne_cmd;
				data->index = data->old_index;
				free(data->key_here);
				data->key_here = NULL;
				// printf("[%s]\n", data->cmd + data->index);
				data->c = '\0';
				data->real_len_cmd = 0;
				return (create_history(data, env));
				// create_history(data, env);
			}
			data->cmd = ft_strjoinaf1(data->cmd, "\n");
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
	return (0);
}

void  add_letter(t_data *data, char buf[6])
{
	data->curs_x++;
	data->cmd = ft_strjoinaf1(data->cmd, buf);
	ft_putchar(buf[0]);
	data->real_len_cmd++;
	data->index++;
	if (data->history_en_cours)
	{
		if (ft_strequ(data->history_en_cours->line, data->history->line) &&
		data->first[0] != '\0' && ft_strequ(data->first, data->cmd))
			data->first = ft_strdup("");
		// else if ()
		// {
		// 	free((data->history_en_cours)->line);
		// 	(data->history_en_cours)->line = ft_strdup(data->cmd);
		// }
	}
}

void	boucle(t_env *env, t_data *data)
{
	char	buf[6];
	int		r;

	data->flag = 0;
	data->first = ft_strdup("");
	ft_bzero(buf, 6);
	while ((r = read(0, buf, 5)))
	{
		if ((ft_isalpha(buf[0]) || (buf[0] >= 32 && buf[0] <= 64) ||
			(buf[0] >= 123 && buf[0] <= 126) || (buf[0] >= 91 && buf[0] <= 96)) &&
			buf[1] == '\0')
			add_letter(data, buf);
		else if (buf[0] == 4 && buf[1] == 0)
			exit(0);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && buf[3] == 0)
			move_left(data);
//			else
//				exec_tcap("bl");
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67 )
			move_right(data);
		else if (buf[0] == 127 && buf[1] == 0)
		{
			if (data->index < 0)
			{}
			else
			{
				delete_use(data);
				if (data->history_en_cours && data->history &&
					ft_strequ(data->history_en_cours->line, data->history->line) &&
					data->index == 0)
					data->first = ft_strdup("");
			}
		}
		else if (buf[0] == 10 && buf[1] == 0)
			create_history(data, env);
		else if (buf[0] == 27	&&	buf[1] == 91	&&	buf[2] == 72 && buf[3] == 0)
			while (data->curs_x > data->len_prompt + 1 && data->curs_x > 0)
				move_left(data);
		else if (buf[0] == 27 && buf[1] == 91	&& buf[2] == 70 && buf[3] == 0)
			while (data->curs_x < data->len_prompt + 1 + (int)data->real_len_cmd)
				move_right(data);
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65 && buf[3] == 0)
		{
			if (data->first[0] == '\0' && data->flag == 0)
				data->first = ft_strdup(data->cmd);
			else if (data->flag == 0)
			{
				data->flag++;
				data->history_en_cours = data->history;
			}
			if (data->history != NULL)
			{
				printf("passe\n");
				move_up_history(data, env);
			}
		}
		else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66 && buf[3] == 0)
		{
			if (data->history != NULL)
				move_down_history(data, env);
		}
		else
		{
			// ft_printf("%d - %d - %d - %d - %d - %d - cursor: x : %d, y : %d\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], data->curs_x, data->curs_y);
		}
		ft_bzero(buf, 6);
	}
}
