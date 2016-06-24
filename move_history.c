/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <adomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:56:45 by adomingu          #+#    #+#             */
/*   Updated: 2016/06/19 00:27:56 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

void	move_up_history(t_data *data, t_env *env, char *cp)
{
	exec_tcap("dl");
	exec_tcap("cr");
	data->prompt = print_prompt(env, data);
	data->len_prompt = ft_strlen(data->prompt) + 2;
   free(data->cmd);
   if (cp[0] != '\0')
   {
      while (!ft_strnstr((data->history_en_cours)->line, cp, ft_strlen(cp)))
      {
         if (!(data->history_en_cours)->prec)
            return ;
         else
            data->history_en_cours = (data->history_en_cours)->prec;
      }
   }
   data->cmd = ft_strdup((data->history_en_cours)->line);
	ft_putstr(data->cmd);
	data->real_len_cmd = ft_strlen(data->cmd);
	data->index = ft_strlen(data->cmd);
	data->curs_x = data->len_prompt + data->real_len_cmd;
	if ((data->history_en_cours)->prec)
		data->history_en_cours = (data->history_en_cours)->prec;
}

void	move_down_history(t_data *data, t_env *env, char *cp)
{
   exec_tcap("dl");
   exec_tcap("cr");
   data->prompt = print_prompt(env, data);
   data->len_prompt = ft_strlen(data->prompt) + 2;
	free(data->cmd);
	if ((data->history_en_cours)->next)
	{
		// ft_putstr("passe");
		data->history_en_cours = (data->history_en_cours)->next;
		if (cp[0] == '\0')
			data->cmd = ft_strdup((data->history_en_cours)->line);
	}
	else if (cp[0] == '\0' && !((data->history_en_cours)->next))
		data->cmd = ft_strdup("");
   else if (cp[0] != '\0')
   {
      if (!(data->history_en_cours)->next)
         data->cmd = ft_strdup(cp);
      else
      {
         while (!ft_strnstr((data->history_en_cours)->line, cp, ft_strlen(cp)))
         {
            if (!(data->history_en_cours))
            {
               data->cmd = ft_strdup(cp);
               break ;
            }
            data->history_en_cours = (data->history_en_cours)->next;
         }
         if (data->history_en_cours)
            data->cmd = ft_strdup((data->history_en_cours)->line);
      }
   }
   ft_putstr(data->cmd);
   data->real_len_cmd = ft_strlen(data->cmd);
   data->index = ft_strlen(data->cmd);
   data->curs_x = data->len_prompt + data->real_len_cmd;
}
