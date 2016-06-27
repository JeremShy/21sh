/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:57:59 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/27 22:27:18 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int			ft_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s=%s\n", env->name, env->arg);
		env = env->next;
	}
	return (1);
}

int			ft_setenv(char **scmd, t_env **env)
{
	if (!scmd[1] || !scmd[2])
		return (0);
	if (isset_arg(*env, scmd[1]))
		change_arg(*env, scmd[1], scmd[2]);
	else
		*env = add_elem_end(*env, scmd[1], scmd[2]);
	return (1);
}

int			ft_unsetenv(char **scmd, t_env **env)
{
	if (!scmd[1])
	{
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
		return (0);
	}
	if (!isset_arg(*env, scmd[1]))
		return (0);
	delete_elem(env, scmd[1]);
	return (1);
}

static int	ft_exit_bi(t_env *env)
{
	delete_list(env);
	exit(EXIT_SUCCESS);
	return (1);
}

int			exec_builtin(char **scmd, t_env **env)
{
	if (ft_strequ(scmd[0], "cd"))
		return (ft_cd(scmd, *env));
	else if (ft_strequ(scmd[0], "env"))
		return (ft_env(*env));
	else if (ft_strequ(scmd[0], "setenv"))
		return (ft_setenv(scmd, env));
	else if (ft_strequ(scmd[0], "unsetenv"))
		return (ft_unsetenv(scmd, env));
	else if (ft_strequ(scmd[0], "exit"))
		return (ft_exit_bi(*env));
	// else if (ft_strequ(sc	md[0], "source"))
		// return (ft_source(scmd, env));
	return (0);
}
