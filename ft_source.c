/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_source.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 14:53:20 by JeremShy          #+#    #+#             */
/*   Updated: 2016/06/01 14:31:55 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int	ft_source(char **scmd, t_env **env)
{
	int		fd;
	char	*cmd;

	if (scmd[1] == '\0')
		return (0);
	fd = open(scmd[1], O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &cmd))
		handle_line(cmd, env);
	return (1);
}
