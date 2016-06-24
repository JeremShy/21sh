/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 20:37:13 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/24 15:15:31 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	is_key(t_data *data)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(data->cmd);
	if (i == 0)
		return (0);
	i--;
	j = i;
	while (j != 0 && data->cmd[j] != '\n')
		j--;
	if (ft_strequ(data->cmd + j + 1, data->key_here))
	{
		data->cmd[j] = '\0';
		return (1);
	}
	return(0);
}
