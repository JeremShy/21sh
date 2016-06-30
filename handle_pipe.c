/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 14:37:12 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/30 16:56:16 by jcamhi           ###   ########.fr       */
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

  /* The first process should get its input from the original file descriptor 0.  */
	cmd->fd_in->fd = 0;
  /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
	i = 0;
	n = find_number(cmd);
	// printf("n : %d\n", n);
	while (i < n - 1)
  {
    pipe(fd);
    /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
		cmd->fd_out->fd = fd[1];
    spawn_proc(cmd, env);
    /* No need for the write end of the pipe, the child will write here.  */
    close(fd[1]);
    /* Keep the read end of the pipe, the next child will read from there.  */
		cmd = cmd->next;
		if (cmd == NULL)
		{
			ft_putstr_fd("21sh: parse error near '|'\n", 2);
			return (-1);
		}
		cmd->fd_in->fd = fd[0];
		i++;
  }
  /* Last stage of the pipeline - set stdin be the read end of the previous pipe
     and output to the original file descriptor 1. */
  if (cmd->fd_in->fd != 0)
    dup2(cmd->fd_in->fd, 0);
  /* Execute the last stage with the current process. */
	file = find_exec(cmd->av[0], env);
	environ = make_env_char(env);
	return (execve(file, cmd->av, environ));
}
