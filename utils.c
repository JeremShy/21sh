/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:51:55 by jcamhi            #+#    #+#             */
/*   Updated: 2016/08/15 23:11:34 by vsteffen         ###   ########.fr       */
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
	else if (ft_strequ(cmd, "cd") || ft_strequ(cmd, "setenv") || ft_strequ(cmd, "unsetenv") ||
			ft_strequ(cmd, "source") || ft_strequ(cmd, "history") || ft_strequ(cmd, "setvar") || ft_strequ(cmd, "unset"))
		return (1);
	else
		return (0);
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
