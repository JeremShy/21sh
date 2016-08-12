#include <sh21.h>

int			ft_env(t_env **env, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!(cmd->av)[1])
		return (print_env(*env, cmd));
	while ((cmd->av)[i] && (cmd->av)[i][0] == '-')
	{
		if ((cmd->av)[i][1] == '-')
			break;
		if (ft_strchr((cmd->av)[i], 'i'))
			data->in_env_i = 1;
		i++;
	}
	return (env_tmp_exec(env, data, cmd->av + i, cmd));
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

void putstr_builtin(t_cmd *cmd, char *str, int fd)
{
	t_fd *fd_ptr;

	if (fd == 1)
		fd_ptr = cmd->fd_out;
	else if (fd == 2)
		fd_ptr = cmd->fd_err;
	else
		return ;
	ft_putstr_fd(str, fd_ptr->fd);
}

int			exec_builtin(t_cmd *cmd, t_env **env, t_data *data)
{

	// if (!cmd->fd_in || cmd->fd_in->fd == -2)
	// 	close(0);
	// else if (cmd->fd_in->fd != 0)
	// 	dup2(cmd->fd_in->fd, 0);
	// if (!cmd->fd_out || cmd->fd_out->fd == -2)
	// 	close(1);
	// else if (cmd->fd_out->fd != 1)
	// 	dup2(cmd->fd_out->fd, 1);
	// if (!cmd->fd_err || cmd->fd_err->fd == -2)
	// 	close(2);
	// else if (cmd->fd_err->fd != 2)
	// 	dup2(cmd->fd_err->fd, 2);
	// signal(SIGINT, SIG_DFL); // Ces dernieres sont les memes qu'a un autre endroit. Anna, je te laisse retrouver et les mettre dans une fonction. On t'aime, bonne chance. Bisous. (Cordialement).
	printf("+-+-+-+-+-+-+-+-+-+ ON PASSE DANS LES BUILTINS\n");
	if (ft_strequ((cmd->av)[0], "cd"))
		return (ft_cd((cmd->av), *env, data));
	else if (ft_strequ((cmd->av)[0], "env"))
		return (ft_env(env, cmd, data));
	else if (ft_strequ((cmd->av)[0], "setenv"))
		return (ft_setenv((cmd->av), env));
	else if (ft_strequ((cmd->av)[0], "unsetenv"))
		return (ft_unsetenv((cmd->av), env));
	else if (ft_strequ((cmd->av)[0], "exit"))
		return (ft_exit_bi((cmd->av), *env, data));
	else if (ft_strequ((cmd->av)[0], "echo"))
		return (ft_echo((cmd->av) + 1));
	else if (ft_strequ((cmd->av)[0], "history"))
		return (ft_history((cmd->av) + 1, data));
	else if (ft_strequ((cmd->av)[0], "setvar"))
		return (ft_setvar((cmd->av), data));
	// else if (ft_strequ(sc	md[0], "source"))
		// return (ft_source(scmd, env));
	return (0);
}
