#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnstr(str, "&&", 2))
		return (ETET);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

int		split_cmd(int count, char *str, t_cmd *cmd, t_hc **heredocs)
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
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		tmp_i = i;
		if(handle_aggr(&i, str, 1, cmd))
		{
		}
		else if (handle_redir(&i, str, 1, cmd, heredocs))
		{
		}
		else if (is_sep(&i, str, 1, cmd))
		{
			return (1);
		}
		else if ((tmp = skip_quotes(str, &i, cmd)) != NULL)
		{
			if (tmp_i != i )
			{
				cmd->av[n_av] = ft_strsub(str, tmp_i, i - tmp_i);
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
	char		*tmp;

	count = 0;
	while (ft_isspace2(str[*i])) // On saute les espaces
		(*i)++;
	if (str[0] == '|') // On regarde si on commence par un pipe.
	{
		ft_putstr_fd("321sh: parse error near '|'\n", 2);
		return (-1);
	}
	// else if (str[*i] == '!' && (ft_isspace2(str[*i + 1]) || str[*i + 1] == '\0')) // pour verifier si le premier caractere est un '!' sans arg --- Flemme de gerer tous les cas, il faut absolument que la commande soit collée au '!'
	// {
	// 	ft_putstr_fd("42sh: syntax error for '!'\n", 2);
	// 	return (-1);
	// }
	while (str[*i])
	{
		while (ft_isspace2(str[*i])) // On saute les espaces
			(*i)++;
		tmp_i = *i;
		if(is_aggr(i, str, 1)) // Si il y a un aggregateur, on le saute.
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
		// else if (is_substitution(str, i, cmd, data) == -1)
		// {
		// 	// printf("PLZ SUBS TO MY CHANNEL\n");
		// 	return (-1);
		// }
		else if ((tmp = skip_quotes_nb_arg(str, i, cmd)) != NULL) // Sinon  on augment notre count.
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

// void	get_pos_after_quote_substitution(size_t *i, char *str)
// {
// 	char open;
//
// 	open = str[*i];
// 	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
// 		(*i)++;
// 	if (str[*i])
// 		(*i)++;
// }

// void	get_pos_after_quote(size_t *i, char *str)
// {
// 	char open;
//
// 	open = str[*i];
// 	while (is_quote_close(open, str[*i + 1]) == 0 && str[*i + 1])
// 		(*i)++;
// 	if (str[*i])
// 		(*i)++;
// }

// char  *get_history_substutition_parsing(t_data *data, char *scmd)
// {
//   char      *str;
//   t_history *list;
//   int       len;
//
//   str = NULL;
//   printf("actual history = [%s]\n", data->history->line);
// 	if (str[0] == '"' && str[1] == '!')
// 		str = str + 2;
// 	else
// 		str = str + 1;
//   if (scmd[0] == '!')
//   {
//     if (data->history != NULL)
//     {
//       data->history = add_history_elem(data->history, create_history_elem(data->cmd));
//       return (ft_strdup(data->history->line));
//     }
//     return (NULL);
//   }
//   else if (ft_isdigit(scmd[0]))
//   {
//     if ((str = history_subsitution_nb_arg_ps(data, scmd)))
//       return (str);
//     return (NULL);
//   }
//   str = NULL;
//   list = data->history;
//   len = (int)ft_strlen(scmd);
//   printf("JE PASSE ICI ! \n");
//   while (list)
//   {
//     if (ft_strnequ(scmd, list->line, len))
//       return (ft_strdup(list->line));
//     list = list->prec;
//   }
//   return (str);
// }


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

// int		substitution_parse(t_data *data, char *str, size_t *i)
// {
// 	t_history	*tmp_history;
// 	char			*subs;
// 	char			*tmp_str;
// 	char			tmp_char;
// 	size_t		after_subs;
//
// 	// if (str[*i] == '"' && str[*i] == "!")
//
// 	if (data->history == NULL || (subs = get_history_substutition(data, str)) == NULL)
// 	{
// 		// data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
// 		ft_putstr_fd("42sh: substitution not found\n", 2);
// 		return (0);
// 	}
// 	printf("ARG FIND -------------> [%s]\n", subs);
// 	exit(0);
// 	after_subs = *i;
// 	// printf("avant ... = [%s]\n", str + after_subs);
// 	while (ft_isspace2(str[after_subs]) == 0 && str[after_subs])
// 		after_subs++;
// 	// printf("after_subs = [%s]\n", str + after_subs);
// 	tmp_char = str[*i];
// 	str[*i] = '\0';
// 	tmp_str = ft_strjoinaf1(subs, str + after_subs);
// 	// printf("first join = [%s] /// ---> subs = [%s] AND str + after_subs = [%s]\n", tmp_str, subs, str + after_subs);
// 	tmp_str = ft_strjoinaf2(str, tmp_str);
// 	str[*i] = tmp_char;
// 	free(str);
// 	str = tmp_str;
// 	*i = after_subs;
// 	data->history = tmp_history;
// 	printf("NEW STR = [%s]\n", str);
// 	return (1);
// }

// int		find_replace_substitution(t_data *data, char *str)
// {
// 	size_t				i;
//
// 	i = 0;
// 	(void)data;
// 	printf("--------------------------------------------\n");
// 	while (str[i])
// 	{
// 		while (ft_isspace2(str[i]))
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		// if (str[i] == '!' || (str[i] == '"' && str[i] == "!"))
// 		// {
// 		// 	if (substitution_parse(data, str, &i) == 0)
// 		// 		return (0);
// 		// 	else
// 		// 		i = 0;
// 		// }
// 		// else
// 			jump_all_quote_for_arg(str, &i);
// 	}
// 	return (1);
// }

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
	if (is_parse_error(str))
		return (NULL);
	if (true_var_and_subs(data, str) == 0)
		return (NULL);
	printf("--------------------------------------------\n");
	printf("RESULTAT : [%s]\n", data->cmd);
	data->history = add_history_elem(data->history, create_history_elem(data->cmd)); // On rajoute la ligne dans l'historique.
	while (str[i])
	{
		fake_cmd.p_error = 0; // On mets le error et le p_error du fake_cmd à 0.
		fake_cmd.error = 0;
		old_i = i; // On retient le i d'avant.
		count = nb_arg(&i, str, &fake_cmd); // On compte le nombre d'elements
		if (count == -1)
		{
			//free cmd.
			return (0);
		}
		if (count)
		{
			if (str[i - 1] == ';')
			{
				cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count, &heredocs));
				exec_cmd(env, cmd, data);
				//FAUDRA FREE CMD.
				cmd = NULL;
			}
			else
			{
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
