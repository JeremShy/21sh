#include <sh21.h>

int find_number(t_cmd *cmd)
{
	int n;

	n = 1;
	while (cmd && cmd->sep == '|')
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

int spawn_proc (t_cmd *cmd, t_env *env, t_data *data, int fd)
{
	pid_t pid;
	int		in;
	int		out;
	int		err;
	char	*file;
	char	**environ;

	in = cmd->fd_in->fd;
	out = cmd->fd_out->fd;
	err = cmd->fd_err->fd;
	if ((pid = fork ()) == 0)
	{
		signal(SIGINT, SIG_DFL);
			dup2(fd, out);
			if (in != 0)
			{
				dup2(in, 0);
				close(in);
			}
			if (out != 1)
			{
				// dup2(out, 1);
				if (cmd->fd_out->fd_pointe == 2)
					dup2(err, 1);
				else
					dup2(out, 1);
				close(out);
			}
			if (err != 2)
			{
				if (cmd->fd_err->fd_pointe == 1)
					dup2(fd, 2);
				else
					dup2(err, 2);
				close(err);
			}
			if (in == -2)
				close(0);
			if (out == -2)
				close(1);
			if (err == -2)
				close(2);
			if (is_builtin(cmd->av[0]))
			{
				cmd->fd_in->fd = 0;
				cmd->fd_out->fd = 1;
				cmd->fd_err->fd = 2;
				cmd->ret = exec_builtin(cmd, &env, data);
				exit(cmd->ret);
			}
			file = find_exec(cmd->av[0], data, env);
			environ = make_env_char(env);
			return execve(file, cmd->av, environ);
		// }
	}
	// else
	// 	waitpid(pid, NULL, 0);
 	if (in != 0)
		close(in);
	return pid;
}

int	fork_pipes(t_cmd *cmd, t_env *env, t_data *data)
{
	int i;
	int fd[2];
	char	*file;
	char	**environ;
	int		n;
	int		fork_exec;
	int		son_proc;
	int		ret_execve;

	// cmd->fd_in->fd = 0;
	i = 0;
	n = find_number(cmd);
	while (i < n - 1)
	{
		pipe(fd);
		if (cmd->fd_out->fd == -2)
			close(fd[1]);
		else
		{
			// dup2(fd[1], cmd->fd_out->fd);
			// cmd->fd_out->fd = fd[1];
		}
		son_proc = spawn_proc(cmd, env, data, fd[1]);
		// printf("SON_PROC = %d\n", son_proc);
		close(fd[1]);
		cmd = cmd->next;
		if (cmd == NULL)
		{
			ft_putstr_fd("221sh: parse error near '|'\n", 2);
			return (-1);
		}
		cmd->fd_in->fd = fd[0];
		i++;
	}
	// printf("on execute : %s\n", cmd->av[0]);
	if (cmd->fd_in->fd != 0)
		dup2(cmd->fd_in->fd, 0);
	if (!cmd->fd_out || cmd->fd_out->fd == -2)
		close(1);
	else if (cmd->fd_out->fd != 1)
		dup2(cmd->fd_out->fd, 1);
	if (!cmd->fd_err || cmd->fd_err->fd == -2)
		close(2);
	else if (cmd->fd_err->fd != 2)
		dup2(cmd->fd_err->fd, 2);
	fork_exec = fork();
	if (fork_exec != 0)
		waitpid(fork_exec, &ret_execve, 0);
	else
	{
		if (is_builtin(cmd->av[0]))
		{
			cmd->fd_in->fd = 0;
			cmd->fd_out->fd = 1;
			cmd->fd_err->fd = 2;
			cmd->ret = exec_builtin(cmd, &env, data);
			exit(cmd->ret);
		}
		file = find_exec(cmd->av[0], data, env);
		environ = make_env_char(env);
		ret_execve = 0;
		return (execve(file, cmd->av, environ));
	}
	wait(NULL);
	exit(get_ret(ret_execve, data));
}
