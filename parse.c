#include <sh21.h>

int				def_sep(char *str)
{
	if (ft_strnequ(str, "&&", 2))
		return (ETET);
	else if (ft_strnequ(str, "||", 2))
		return (OUOU);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == ';')
		return (str[0]);
	return (0);
}

int				split_cmd(int count, char **str, t_cmd *cmd, t_hc **heredocs)
{
	size_t		tmp_i;
	char		*tmp;
	size_t		i;
	int			n_av;

	i = 0;
	cmd->av = (char**)malloc((count + 1) * sizeof(char*));
	cmd->av[count] = 0;
	n_av = 0;
	while ((*str)[i])
	{
		while (ft_isspace2((*str)[i]))
			i++;
		tmp_i = i;
		if (handle_aggr(&i, (*str), 1, cmd))
		{
		}
		else if (handle_redir(&i, &(*str), 1, cmd, heredocs))
		{
		}
		else if (is_sep(&i, (*str), 1, cmd))
		{
			return (1);
		}
		else if ((tmp = skip_quotes(&(*str), &i, cmd)) != NULL)
		{
			if (tmp_i != i)
			{
				cmd->av[n_av] = tmp;
				n_av++;
			}
		}
		if (cmd->error)
		{
			return (-1);
		}
	}
	return (1);
}

static void		parse_init(t_data *data, size_t *i, t_hc **heredocs)
{
	*i = 0;
	data->parse_heredocs = heredocs;
	data->command = NULL;
}

static void		count_and_init_command(t_data *data, t_cmd *fake_cmd,
	char *str, size_t *i)
{
	fake_cmd->p_error = 0;
	fake_cmd->error = 0;
	data->parse_old_i = *i;
	data->parse_count = nb_arg(i, str, fake_cmd);
}

static t_cmd	*free_cmd_and_return(t_data *data)
{
	delete_list_command(data->command);
	data->command = NULL;
	return (NULL);
}

t_cmd			*parse(char *str, t_hc *heredocs, t_env **env, t_data *data)
{
	size_t		i;
	t_cmd		fake_cmd;
	t_cmd		*last;

	parse_init(data, &i, &heredocs);
	if (is_pipe_error(str))
		return (NULL);
	data->history = add_history_elem(data->history, create_history_elem(str));
	while (str[i])
	{
		count_and_init_command(data, &fake_cmd, str, &i);
		if (data->parse_count == -1)
			return (free_cmd_and_return(data));
		if (data->parse_count && !add_command(data, str, &i, env))
			return (NULL);
	}
	if (!data->command)
		return (NULL);
	last = data->command;
	while (last->next)
		last = last->next;
	return (data->command);
}
