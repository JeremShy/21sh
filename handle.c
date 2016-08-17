#include <sh21.h>

int		handle_aggr(size_t *i, char *str, int jump, t_cmd *cmd)
{
	size_t 	tmp;
	int			avant;
	int			apres;
	char		chevron;
	t_fd		**fd_avant;
	t_fd		**fd_apres;

	tmp = *i;
	avant = 1;
	if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == '&' && (ft_isdigit(str[*i + 2]) || str[*i + 2] == '-')) // On check si le truc est valide.
	{
		chevron = str[*i];
		(*i) += 2;
		if (str[*i] == '-')
			apres = -2;
		else
			apres = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
	}
	else if (ft_isdigit(str[*i]) && (str[*i + 1] == '>' || str[*i + 1] == '<') && str[*i + 2] == '&' && (ft_isdigit(str[*i + 3]) || str[*i + 3] == '-')) // La meme
	{
		avant = str[*i] - '0';
		chevron = str[*i + 1];
		(*i) += 3;
		if (str[*i] == '-')
			apres = -2;
		else
			apres = ft_atoi(str + *i);
		while (ft_isdigit(str[*i]) || str[*i] == '-')
			(*i)++;
		if (!jump)
			*i = tmp;
	}
	else
		return (0);
	if (avant == 0) // On mets des pointeurs sur le fd_avant et le fd_apres (format fd_avant>&fd_apres).
		fd_avant = &cmd->fd_in;
	else if (avant == 1)
		fd_avant = &cmd->fd_out;
	else if (avant == 2)
		fd_avant = &cmd->fd_err;
	if (apres == 0)
		fd_apres = &cmd->fd_in;
	else if (apres == 1)
		fd_apres = &cmd->fd_out;
	else
		fd_apres = &cmd->fd_err;
	if (chevron == '>')
	{
		if ((*fd_apres)->fd == -1 && apres != -2) // Si c'est le premier fd qu'on redefinit, on remplace.
		{
			*fd_avant = add_fd_elem(*fd_avant, create_fd(dup(apres)));
		}
		else if (apres != -2)
			*fd_avant = add_fd_elem(*fd_avant, copy_fd(*fd_apres)); // Si on le close pas, on ajoute a la liste.
		else
			*fd_avant = add_fd_elem(*fd_avant, create_fd(-2)); // Sinon, on le close. (tout ce bordel etait pour ne pas faire un dup(-2) !)
	}
	else
	{
		if (apres == -2)
			*fd_avant = add_fd_elem(*fd_avant, create_fd(-2)); // Sinon, on le close. (tout ce bordel etait pour ne pas faire un dup(-2) !)
	}
	printf ("err : \n");
	print_fd(cmd->fd_err);
	printf ("out : \n");
	print_fd(cmd->fd_out);
	return (1);
}

char	*handle_redir(size_t *i, char **str, int jump, t_cmd *cmd, t_hc **heredocs)
{
	size_t	tmp;
	char		*quote;
	int			fd;
	int			fd_file;
	int			pipe_tab[2];
	int			redir_type; //0 : >, 1 : >>, 2 <, 3 <<

	fd_file = -1;
	tmp = *i;
	fd = ((*str)[tmp] == '>' ? 1 : 0);
	if (((*str)[tmp] == '<' && (*str)[tmp + 1] == '<') || ((*str)[tmp] == '>' && (*str)[tmp + 1] == '>')) // on check si la redirection est valide.
	{
		redir_type = ((*str)[tmp] == '<' ? 3 : 1);
		tmp += 2;
	}
	else if ((*str)[tmp] == '<' || (*str)[tmp] == '>')
	{
		redir_type = ((*str)[tmp] == '>' ? 0 : 2);
		tmp++;
	}
	else if (ft_isdigit((*str)[*i]))
	{
		fd = (*str)[*i] - '0';
		if ((*str)[tmp + 1] == '>' && (*str)[tmp + 2] == '>')
		{
			redir_type = 1;
			tmp += 3;
		}
		else if ((*str)[tmp + 1] == '>')
		{
			redir_type = 0;
			tmp += 2;
		}
		else
			return (NULL);
	}
	if (tmp != *i) // Si on a bouge tmp, alors :
	{
		while (ft_isspace2((*str)[tmp])) // on saute les espaces
			tmp++;
		if (is_empty(*str, &tmp)) // on check si c'est empty
		{
			cmd->p_error = 1;
			return(NULL);
		}
		quote = skip_quotes(str, &tmp, cmd); // on vire les quotes
		if (!quote)
			quote = ft_strdup("");
		if (fd > 2)
			return(quote); // si le fd est pourri, on se barre
		// printf("Quote : [%s]. fd : %d\n", quote, fd);
		if (redir_type == 0) // on open avec les bons flags selon si c'est  > ou >> ou <
			fd_file = open(quote, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir_type == 1)
			fd_file = open(quote, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir_type == 2)
		{
			if ((fd_file = open(quote, O_RDONLY)) < 0) // si on peut pas open en read, on affiche une erreur et on termine le parsing.
			{
				ft_putstr_fd("zsh: error while opening file: ", 2);
				ft_putstr_fd(quote, 2);
				ft_putstr_fd("\n", 2);
				cmd->error = 1;
				free(quote);
				return(NULL);
			}
		}
		else if (redir_type == 3)
		{
			if (pipe(pipe_tab) == -1)
			{
				ft_putstr_fd("zsh: error while handling heredoc. \n", 2);
				cmd->error = 1;
				free(quote);
				return(NULL);
			}
			// printf("value of (*heredocs) = [%s]\n", (*heredocs)->content);
			write(pipe_tab[1], (*heredocs)->content, ft_strlen((*heredocs)->content));
			// printf("We write in heredocs : %s\n", (*heredocs)->content);
			close(pipe_tab[1]);
			fd_file = pipe_tab[0];
			*heredocs = (*heredocs)->next;
		}
		if (fd_file == -1)
		{
			if (access(quote, F_OK) == -1)
			{
				ft_putstr_fd("21sh: no such file or directory: ", 2);
				ft_putendl_fd(quote, 2);
			}
			else if ((redir_type == 0 || redir_type == 1) && access(quote, W_OK) == -1)
			{
				ft_putstr_fd("21sh: permission denied: ",2);
				ft_putendl_fd(quote, 2);
			}
			else if (redir_type == 1 && access(quote, R_OK) == -1)
			{
				ft_putstr_fd("21sh: permission denied: ",2);
				ft_putendl_fd(quote, 2);
			}
			else
			{
				ft_putendl_fd("21sh: Error while opening the file: ", 2);
				ft_putendl_fd(quote, 2);
			}
			cmd->error = 1;
			return (NULL);
		}
		if (fd == 0) // on ajoute ce truc au bon fd.
			cmd->fd_in = add_fd_elem(cmd->fd_in, create_fd(fd_file));
		else if (fd == 1)
			cmd->fd_out = add_fd_elem(cmd->fd_out, create_fd(fd_file));
		else if (fd == 2)
			cmd->fd_err = add_fd_elem(cmd->fd_err, create_fd(fd_file));
		if (jump)
			*i = tmp;
		// printf("redir_type : %d\n", redir_type);
		// close(fd);
		// dup(fd_file);
		// dup2(fd, fd_file);
		// write(fd, "a\n", 2);
		return (quote);
	}
	return (NULL);
}
