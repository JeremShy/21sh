/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_flag_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsteffen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:33:07 by vsteffen          #+#    #+#             */
/*   Updated: 2016/09/01 17:33:13 by vsteffen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			history_flag_p(char **scmd, t_cmd *cmd)
{
	int		j;

	j = 0;
	while (scmd[j] != NULL)
	{
		putstr_builtin(cmd, scmd[j], 1);
		putchar_builtin(cmd, '\n', 1);
		j++;
	}
	return (0);
}
