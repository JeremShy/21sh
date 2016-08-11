#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnequ(str, "&&", 2))
		return (ETET);
	else if (ft_strnequ(str, "||", 2))
		return (OUOU);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

int		split_cmd(int count, char **str, t_cmd *cmd, t_hc **heredocs)
{
	size_t 	tmp_i;
	char		*tmp;
	size_t	i;
	int			n_av;

	i = 0;
	cmd->av = (char**)malloc((count + 1) * sizeof(char*));
	cmd->av[count] = 0;
	n_av = 0;
	// printf("[%s]\n", str);
	while ((*str)[i])
	{
		while (ft_isspace2((*str)[i]))
			i++;
		tmp_i = i;
		if(handle_aggr(&i, (*str), 1, cmd))
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
			if (tmp_i != i )
			{
				// cmd->av[n_av] = ft_strsub(str, tmp_i, i - tmp_i);
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

int nb_arg(size_t *i, char *str, t_cmd *cmd)
{
	int			count;
	size_t 	tmp_i;

	count = 0;
	while (ft_isspace2(str[*i])) // On saute les espaces
		(*i)++;
	if (str[0] == '|') // On regarde si on commence par un pipe.
	{
		ft_putstr_fd("321sh: parse error near '|'\n", 2);
		return (-1);
	}
	while (str[*i])
	{
		while (ft_isspace2(str[*i])) // On saute les espaces
		{
			(*i)++;
		}
		tmp_i = *i;
		if (is_aggr(i, str, 1)) // Si il y a un aggregateur, on le saute.
		{
			// printf("IT'S ALIVE\n");
		}
		else if (is_redir(i, str, 1, cmd)) // Si il y a une redirection, on la saute (comme la mere de vivien).
		{
			// printf("TYPICAL PENIS\n");
		}
		else if (is_sep(i, str, 1, cmd)) // Si il y a un separateur, on return
		{
			// printf("RIP ORIGINALITE\n");
			return (count);
		}
		else if (skip_quotes_nb_arg(str, i, cmd) != NULL) // Sinon  on augmente notre count.
		{
			// printf("J'AIME LE CACA\n");
			if (tmp_i != *i)
			{
				count++;
			}
		}
		if (cmd->p_error) // Si il y a une parse_error on return.
		{
			ft_putstr_fd("21sh: parse error\n", 2);
			return (-1);
		}
	}
	return (count);
}

void	jump_all_quote_for_arg(char *str, size_t *i)
{
	char		open_quote;
	size_t	begin_quote;

	// printf("FIRST CHAR = '%c'\n", str[*i]);
	while (ft_isspace2(str[*i]) == 0 && str[*i])
	{
		if (is_quote_open(str[*i]))
		{
			open_quote = str[*i];
			get_pos_after_quote(i, str);
			begin_quote = *i;
			// printf("char after quote = [%c]\n", str[*i]);
			(*i)++;
			// printf("car = '%c'\n", str[*i]);
		}
		else
			(*i)++;
	}
	// printf("END CHAR = '%c'\n", str[*i - 1]);
}

t_cmd	*parse(char *str, t_hc *heredocs, t_env **env, t_data *data)
{
	int		count;
	size_t	i;
	size_t	old_i;
	t_cmd		*cmd;
	t_cmd		fake_cmd; //Important.
	t_cmd		*last;

	// printf("str : [%s]\n", str);
	i = 0;
	cmd = NULL; // On initialiase notre retour.
	if (is_pipe_e_parse_error(str))
		return (NULL);
	if (true_var_and_subs(data, &str) == 0)
		return (NULL);
	data->history = add_history_elem(data->history, create_history_elem(str)); // On rajoute la ligne dans l'historique.
	while (str[i])
	{
		fake_cmd.p_error = 0; // On mets le error et le p_error du fake_cmd à 0.
		fake_cmd.error = 0;
		old_i = i; // On retient le i d'avant.
		// printf("STR  = [%s]\n", str);
		count = nb_arg(&i, str, &fake_cmd); // On compte le nombre d'elements
		if (count == -1)
 		{
			//free cmd.
			return (0);
		}
		if (count)
		{
			printf("--------------------------------------------\n");
			printf("RESULTAT : [%s] - count : %d\n", str , count);
			if (str[i - 1] == ';')
			{
				cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count, &heredocs));
				exec_cmd(env, cmd, data);
				//FAUDRA FREE CMD.
				cmd = NULL;
			}
			else
			{
				// printf("STR2 = [%s]\n", str);
				cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count, &heredocs)); //count a bouge i, du coup i - old_i donne le taille de la chaine a envoyer à create cmd_elem.
			}
		}
	}
	if (!cmd)
		return (NULL);
	last = cmd;
	while (last->next)
		last = last->next;
	if (last->sep == '|')
	{
		ft_putendl_fd("421sh: parse error near '|'", 2);
		return (NULL);
	}
	return (cmd);
}
