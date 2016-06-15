/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/15 14:59:26 by jcamhi           ###   ########.fr       */
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

int		split_cmd(int count, char *str, t_cmd *cmd)
{
	size_t 	tmp_i;
	char		*tmp;
	size_t	i;
	int			n_av;

	i = 0;
	cmd->av = (char**)malloc((count + 1) * sizeof(char*));
	n_av = 0;
	printf("[%s]\n", str);
	while (str[i])
	{
		while (ft_isspace2(str[i]))
			i++;
		tmp_i = i;
		if(handle_aggr(&i, str, 1, cmd))
		{
		}
		else if (handle_redir(&i, str, 1, cmd))
		{
		}
		else if (is_sep(&i, str, 1))
		{
			if (i == 0)
				cmd->sep = NONE;
			else
				cmd->sep = def_sep(str + i - 1);
			return (1);
		}
		else if ((tmp = skip_quotes(str, &i, cmd)) != NULL)
		{
			if (tmp_i != i )
			{
				cmd->av[n_av] = ft_strsub(str, tmp_i, i - tmp_i);
				cmd->av[n_av + 1] = 0;
				n_av++;
			}
		}
		if (cmd->error)
			return (0);
	}
	cmd->sep = NONE;
	return (1);
}

int nb_arg(size_t *i, char *str, t_cmd *cmd)
{
	int			count;
	size_t 	tmp_i;
	char		*tmp;

	count = 0;
	if (str[0] == '|')
	{
		ft_putstr_fd("21sh: parse error near '|'\n", 2);
		return (-1);
	}
	while (str[*i])
	{
		while (ft_isspace2(str[*i]))
			(*i)++;
		tmp_i = *i;
		if(is_aggr(i, str, 1))
		{
			// printf("IT'S ALIVE\n");
		}
		else if (is_redir(i, str, 1, cmd))
		{
			// printf("TYPICAL PENIS\n");
		}
		else if (is_sep(i, str, 1))
		{
			// printf("RIP ORIGINALITE\n");
			return (count);
		}
		else if ((tmp = skip_quotes_nb_arg(str, i, cmd)) != NULL)
		{
			// printf("J'AIME LE CACA\n");
			if (tmp_i != *i)
			{
				count++;
			}
		}
		if (cmd->p_error)
		{
			ft_putstr_fd("21sh: parse error\n", 2);
			return (-1);
		}
	}
	return (count);
}

t_cmd	*parse(char *str)
{
	int		count;
	size_t	i;
	size_t	old_i;
	t_cmd		*cmd;
	t_cmd		fake_cmd; //Important.
	t_cmd		*tmp;

	// printf("on recoit : [%s]\n", str);
	i = 0;
	cmd = NULL;
	while (str[i])
	{
		fake_cmd.p_error = 0;
		fake_cmd.error = 0;
		old_i = i;
		count = nb_arg(&i, str, &fake_cmd);
		// printf("str : %s\n", str + i);
		if (count == -1)
		{
			//free cmd.
			return (0);
		}
		// printf("RESULTAT DE COUNT = [%d]\n", count);
		cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i), count));
		// t_cmd *cmd; // = parse(av[1]);
	}

	// print_list(cmd);
	tmp = cmd;
	while (cmd)
	{
		if (cmd->fd_in->fd == -1)
			cmd->fd_in->fd = 0;
		if (cmd->fd_out->fd == -1)
			cmd->fd_out->fd = 1;
		if (cmd->fd_err->fd == -1)
			cmd->fd_err->fd = 2;
		cmd = cmd->next;
	}
	return (tmp);
}
