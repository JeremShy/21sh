/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_advanced_subs_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:09 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:14 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

static void	is_subs_and_replace_init(t_data *data, size_t *length,
	size_t *index, int flag)
{
	*length = *index + 1;
	data->flag_enter = 1;
	data->subs_index = *index;
	data->subs_flag = flag;
}

static void	is_subs_and_replace_end_of_if(t_data *data, size_t *index)
{
	(*index)--;
	data->flag_enter = 0;
}

int			is_subs_and_replace(t_data *d, char **str, size_t *index, int flag)
{
	size_t	length;
	char	*arg;

	is_subs_and_replace_init(d, &length, index, flag);
	if (!is_escaped_char(*str, *index) && (*str)[*index] == '!')
	{
		if ((*str)[length] == '!')
		{
			if (!subs_for_last_command(d, &arg, &length))
				return (0);
		}
		else if (ft_isdigit((*str)[length]))
		{
			if (!subs_for_command_number(d, &arg, str, &length))
				return (0);
		}
		else
		{
			if (!subs_default(d, &arg, str, &length))
				return (0);
		}
		delete_subs_and_replace(str, *index, length, arg);
		is_subs_and_replace_end_of_if(d, index);
	}
	return (1);
}
