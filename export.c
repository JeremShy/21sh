/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adomingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 17:30:24 by adomingu          #+#    #+#             */
/*   Updated: 2016/09/01 17:30:32 by adomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			ft_export(char **scmd, t_env **env, t_cmd *cmd)
{
	char *arg;

	if (!scmd[1])
	{
		print_env(*env, cmd);
		return (0);
	}
	if (scmd[2])
		arg = ft_strdup(scmd[2]);
	else
		arg = ft_strdup("");
	if (isset_arg(*env, scmd[1]))
		change_arg(*env, scmd[1], arg);
	else
		*env = add_elem_end(*env, scmd[1], arg);
	free(arg);
	return (0);
}
