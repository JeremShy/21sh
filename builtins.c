#include <sh21.h>

int			ft_env(t_env **env, char **scmd, t_data *data)
{
	int	i;

	i = 1;
	if (!scmd[1])
		return (print_env(*env));
	while (scmd[i] && scmd[i][0] == '-')
	{
		if (scmd[i][1] == '-')
			break;
		if (ft_strchr(scmd[i], 'i'))
			data->in_env_i = 1;
		i++;
	}
	return (env_tmp_exec(env, data, scmd + i));
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

static int	ft_exit_bi(char **scmd, t_env *env, t_data *data)
{
	history_exit(data);
	delete_list(env);
	if (scmd[1])
		exit(ft_atoi(scmd[1]));
	else
		exit(EXIT_SUCCESS);
	return (1);
}

int			exec_builtin(char **scmd, t_env **env, t_data *data)
{
	if (ft_strequ(scmd[0], "cd"))
		return (ft_cd(scmd, *env, data));
	else if (ft_strequ(scmd[0], "env"))
		return (ft_env(env, scmd, data));
	else if (ft_strequ(scmd[0], "setenv"))
		return (ft_setenv(scmd, env));
	else if (ft_strequ(scmd[0], "unsetenv"))
		return (ft_unsetenv(scmd, env));
	else if (ft_strequ(scmd[0], "exit"))
		return (ft_exit_bi(scmd, *env, data));
	else if (ft_strequ(scmd[0], "echo"))
		return (ft_echo(scmd + 1));
	else if (ft_strequ(scmd[0], "history"))
		return (ft_history(scmd + 1, data));
	else if (ft_strequ(scmd[0], "setvar"))
		return (ft_setvar(scmd, data));
	// else if (ft_strequ(sc	md[0], "source"))
		// return (ft_source(scmd, env));
	return (0);
}
