/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/07/18 18:24:02 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (str[0] == '|') // On regarde si on commence par un pipe.
	{
		ft_putstr_fd("321sh: parse error near '|'\n", 2);
		return (-1);
	}
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

t_cmd	*parse(char *str, t_hc *heredocs, t_env **env, t_data *data)
{
	int		count;
	size_t	i;
	size_t	old_i;
	t_cmd		*cmd;
	t_cmd		fake_cmd; //Important.
	t_cmd		*last;

	printf("str : [%s]\n", str);
	i = 0;
	cmd = NULL; // On initialiase notre retour.
	if (is_parse_error(str))
		return (NULL);
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
					// cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count, &heredocs));
					// last = cmd;
					// while (last && last->av[0])
					// 	last = last->next;
					// if (!last)
					// 	ft_putendl_fd("21sh: parse error", 2);
					// // else
					// 	exec_cmd(env, cmd);
					// //FAUDRA FREE CMD.
					// cmd = NULL;
					// cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count, &heredocs));
				// last = cmd;
				// while (last && last->av[0])
				// {
				// 	printf ("command : %s\n", last->av[0]);
				// 	last = last->next;
				// }
				// if (!last)
				// 	ft_putendl_fd("21sh: parse error", 2);
				// else
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
