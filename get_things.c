/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:30:24 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 17:30:32 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		get_actual_line(t_data *data)
{
	return ((data->len_prompt + data->index + 1) / data->win_x);
}

int		get_line_max(t_data *data)
{
	return ((data->len_prompt + (int)ft_strlen(data->cmd) + 1) / data->win_x);
}

int		get_prompt_line(t_data *data)
{
	return (data->len_prompt / data->win_x);
}
