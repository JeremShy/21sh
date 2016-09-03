/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_advanced_subs_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 22:32:32 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/03 22:32:33 by adomingu         ###   ########.fr       */
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
	data->subs_for_first_char = 0;
}

static void	is_subs_and_replace_end_of_if(t_data *data, size_t *index)
{
	if (!data->subs_for_first_char)
		(*index)--;
	data->flag_enter = 0;
}

int			cradoc_for_first_char(size_t *index, t_data *data)
{
	if (*index == 0)
		data->subs_for_first_char = 1;
	return (1);
}

int			is_subs_and_replace(t_data *d, char **str, size_t *index, int flag)
{
	size_t	length;
	char	*arg;

	is_subs_and_replace_init(d, &length, index, flag);
	if (!is_escaped_char(*str, *index) && (*str)[*index] == '!')
	{
		if (cradoc_for_first_char(index, d) && (*str)[length] == '!')
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
