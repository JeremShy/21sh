/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:37:12 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/06 20:46:08 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int spawn_proc (t_cmd *cmd, t_env *env)
{
	pid_t pid;
	int		in;
	int		out;
	char	*file;
	char	**environ;

	in = cmd->fd_in->fd;
	out = cmd->fd_out->fd;
	if ((pid = fork ()) == 0)
	{
		printf("xlaunching command : %s\n", cmd->av[0]);
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		file = find_exec(cmd->av[0], env);
		environ = make_env_char(env);
		return execve(file, cmd->av, environ);
	}
	if (in != 0)
		close(in);
	return pid;
}

int	fork_pipes(t_cmd *cmd, t_env *env)
{
	int i;
	int fd[2];
	char	*file;
	char	**environ;
	int		n;

	cmd->fd_in->fd = 0;
	i = 0;
	n = find_number(cmd);
	// printf("n : %d\n", n);
	while (i < n - 1)
	{
		pipe(fd);
		cmd->fd_out->fd = fd[1];
		spawn_proc(cmd, env);
		close(fd[1]);
		cmd = cmd->next;
		if (cmd == NULL)
		{
			ft_putstr_fd("21sh: parse error near '|'\n", 2);
			return (-1);
		}
		cmd->fd_in->fd = fd[0];
		i++;
	}
	printf("launching command : %s\n", cmd->av[0]);
	if (cmd->fd_in->fd != 0)
		dup2(cmd->fd_in->fd, 0);
	file = find_exec(cmd->av[0], env);
	environ = make_env_char(env);
	return (execve(file, cmd->av, environ));
}
