/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:56:45 by adomingu          #+#    #+#             */
/*   Updated: 2016/06/17 03:52:20 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	move_up_history(t_data *data, t_env *env, char *cp)
{
      char  *str;

      str = NULL;
		exec_tcap("dl");
		exec_tcap("cr");
		data->prompt = print_prompt(env, data);
		data->len_prompt = ft_strlen(data->prompt);
		if (data->history_en_cours == NULL)
			data->history_en_cours = data->history;
      str = ft_strdup (data->history_en_cours->line);
      free(data->cmd);
      if (!ft_strnstr(data->history_en_cours->line, cp, ft_strlen(cp)) && cp[0] != '\0')
      {
         while (data->history_en_cours)
         {
            if (ft_strnstr(data->history_en_cours->line, cp, ft_strlen(cp)))
            {
               data->cmd = ft_strdup(data->history_en_cours->line);
               break ;
            }
            if (!(data->history_en_cours))
            {
               data->cmd = ft_strdup(str);
               free(str);
               break ;
            }
            data->history_en_cours = (data->history_en_cours)->next;
         }
      }
      else
         data->cmd = ft_strdup(data->history_en_cours->line);
		ft_putstr(data->cmd);
		data->real_len_cmd = ft_strlen(data->cmd);
		data->index = ft_strlen(data->cmd);
		data->curs_x = data->len_prompt + data->real_len_cmd + 1;
		if ((data->history_en_cours)->prec)
			data->history_en_cours = (data->history_en_cours)->prec;
}

void	move_down_history(t_data *data, t_env *env, char *cp)
{
	// if (data->c == '\0')
	// {
		exec_tcap("dl");
		exec_tcap("cr");
		data->prompt = print_prompt(env, data);
		data->len_prompt = ft_strlen(data->prompt);
		if (data->history_en_cours == NULL)
			data->history_en_cours = data->history;
      free(data->cmd);
      if ((data->history_en_cours)->next)
         data->history_en_cours = (data->history_en_cours)->next;
		if (!(data->history_en_cours)->next && cp[0] == '\0')
         data->cmd = ft_strdup("");
      else if (!(data->history_en_cours)->next && cp[0] != '\0')
         data->cmd = ft_strdup(cp);
      if (cp[0] == '\0' && (data->history_en_cours)->next)
         data->cmd = ft_strdup((data->history_en_cours)->line);
      else if (cp[0] != '\0' && (data->history_en_cours)->next)
      {
         while ((data->history_en_cours))
         {
            if (ft_strnstr(data->history_en_cours->line, cp, ft_strlen(cp)))
            {
               data->cmd = ft_strdup((data->history_en_cours)->line);
               break ;
            }
            if (!(data->history_en_cours)->next)
            {
               data->cmd = ft_strdup(cp);
               break ;
            }
            data->history_en_cours = (data->history_en_cours)->next;
         }
      }
		ft_putstr(data->cmd);
		data->real_len_cmd = ft_strlen(data->cmd);
		data->index = ft_strlen(data->cmd);
		data->curs_x = data->len_prompt + data->real_len_cmd;
   // }
}
