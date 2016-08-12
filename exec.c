#include <sh21.h>

static char	*print_error_no_path(char *tmp)
{
	ft_putstr_fd("Error : The value of the environment variable PATH", 2);
	ft_putstr_fd(" is not valid or inexistant.\n", 2);
	free(tmp);
	return (NULL);
}

static char	*while_exec(char **split, char *scmd)
{
	int			i;
	DIR			*directory;
	t_dirent	*truc;

	i = 0;
	while (split[i])
	{
		directory = opendir(split[i]);
		while (directory && (truc = readdir(directory)))
			if (ft_strequ(truc->d_name, scmd) &&
					!ft_strequ(truc->d_name, ".") &&
					!ft_strequ(truc->d_name, ".."))
			{
				closedir(directory);
				return (ft_strjoinaf1(ft_strjoin(split[i], "/"), scmd));
			}
		if (directory)
			closedir(directory);
		i++;
	}
	ft_putstr_fd("21sh: command not found: ", 2);
	ft_putstr_fd(scmd, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

char		*find_exec(char *scmd, t_env *list)
{
	char	**split;
	char	*tmp;
	char	*ret;

	if (ft_strchr(scmd, '/'))
		return (ft_strdup(scmd));
	tmp = find_arg(list, "PATH");
	if (ft_strequ(tmp, ""))
		return (print_error_no_path(tmp));
	split = ft_strsplit(tmp, ':');
	free(tmp);
	ret = while_exec(split, scmd);
	free_char_tab(split);
	return (ret);
}


int			exec_file(t_cmd *cmd, t_env *list, int in_env_i)
{
	char	*file;
	char	**env;
	pid_t	process;
	int		retour;

	file = find_exec(cmd->av[0], list);
	if (!file)
		return (0);
	if (access(file, X_OK) == -1)
	{
		if (in_env_i)
			ft_putstr_fd("env: permission denied: ", 2);
		else
			ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putendl_fd(cmd->av[0], 2);
		free(file);
		return (0);
	}
	if (in_env_i)
		env = make_env_char(NULL);
	else
		env = make_env_char(list);
	// printf("in : %d - out : %d - err - %d - command : %s\n", cmd->fd_in->fd, cmd->fd_out->fd, cmd->fd_err->fd, file);
	process = fork();
	if (process != 0)
		wait(NULL);
	else
	{
		if (!cmd->fd_in || cmd->fd_in->fd == -2)
			close(0);
		else if (cmd->fd_in->fd != 0)
			dup2(cmd->fd_in->fd, 0);
		if (!cmd->fd_out || cmd->fd_out->fd == -2)
			close(1);
		else if (cmd->fd_out->fd != 1)
			dup2(cmd->fd_out->fd, 1);
		if (!cmd->fd_err || cmd->fd_err->fd == -2)
			close(2);
		else if (cmd->fd_err->fd != 2)
			dup2(cmd->fd_err->fd, 2);
		signal(SIGINT, SIG_DFL);
		retour = execve(file, cmd->av, env);
		if (retour == -1)
		{
			if (in_env_i)
				ft_putstr_fd("env: exec format error: ", 2);
			else
				ft_putstr_fd("21sh: exec format error: ", 2);
			ft_putendl_fd(cmd->av[0], 2);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	free_char_tab(env);
	return (1);
}

t_cmd		*cmd_not_found(t_env *list, t_cmd *command)
{
	t_cmd		*last_found;
	char		*exec;
	int			ok;
	int			was_ok;

	last_found = NULL;
	ok = 0;
	was_ok = 1;
	if (command->sep != '|')
		return (command);
	while (command && (command->sep == '|' || was_ok))
	{
		if (command->sep != '|')
			was_ok = 0;
		if (!(exec = find_exec(command->av[0], list)))
		{
			ok = 0;
			printf("COMMAND NOT FOUND CONNARD\n");
			last_found = NULL;
		}
		else if (!ok)
		{
			ok = 1;
			last_found = command;
			free(exec);
		}
		command = command->next;
	}

	/*if (last_found)
		printf("on renvoit : %s\n", last_found->av[0]);
	else
		printf("on renvoit rien;");*/
	return (last_found);
}

void		exec_cmd(t_env **env, t_cmd *command, t_data *data)
{
	t_cmd *temp;
	pid_t pid;

	if (!command)
		return;
	temp = command;
	// print_list(command);
	command = cmd_not_found(*env, command);
	while (command && (command->fd_in || command->fd_out || command->fd_err))
	{
		if (command->av[0] && (command->sep == NONE || command->sep == POINT_VIRGULE || command->sep == ETET))
		{
			if (is_builtin(command->av[0]))
				exec_builtin(command->av, env, data);
			else
			{
				exec_file(command, *env, data->in_env_i);
			}
			// printf("\nend of command.\n");
			if (command->fd_out || command->fd_in || command->fd_err)
			{
				if (command->fd_out)
					command->fd_out = command->fd_out->next;
				if (command->fd_err)
					command->fd_err = command->fd_err->next;
				if (command->fd_in)
					command->fd_in = command->fd_in->next;
			}
			else
				command = command->next;
		}
		else if (command->sep == '|')
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			else
			{
				signal(SIGINT, SIG_DFL);
				if (fork_pipes(command, *env) == -1)
					exit(0);
			}
			while (command && command->sep == '|')
					command = command->next;
			if (command)
			{
				command = command->next;
				if (command)
					command = cmd_not_found(*env, command);
			}
		}
		// if (command && !(command->fd_in || command->fd_out || command->fd_err))
		// {
		// 	// Ici
		// 	command = command->next;
		// }
	}
	//free temp.
	close_fd_cmd(temp);
}
