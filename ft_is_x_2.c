/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_x_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		is_builtin(char *cmd)
{
	if (cmd[0] == 'e')
	{
		if (ft_strequ(cmd, "exit") || ft_strequ(cmd, "env") ||
			ft_strequ(cmd, "echo") || ft_strequ(cmd, "export"))
			return (1);
		else
			return (0);
	}
	else if (ft_strequ(cmd, "cd") || ft_strequ(cmd, "setenv")
		|| ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "source")
		|| ft_strequ(cmd, "history") || ft_strequ(cmd, "setvar")
		|| ft_strequ(cmd, "unset"))
		return (1);
	else
		return (0);
}

int		is_key(t_data *data)
{
	if (ft_strequ(data->cmd, data->key_here))
		return (1);
	return (0);
}
