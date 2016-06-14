/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 18:50:48 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		split_cmd(int count, char *str, t_cmd *cmd)
{
	size_t 	tmp_i;
	char		*tmp;
	size_t	i;
	int			n_av;

	i = 0;
	cmd->av = (char**)malloc((count + 1) * sizeof(char*));
	n_av = 0;
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

int main(int ac, char **av)
{
	int		count;
	char 	*str;
	size_t	i;
	size_t	old_i;
	t_cmd		*cmd;
	t_cmd		fake_cmd; //Important.

	if (ac == 1)
	{
		printf("KAKA\n");
		return (0);
	}
	str = av[1];
	printf("on recoit : [%s]\n", str);
	i = 0;
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
		printf("RESULTAT DE COUNT = [%d]\n", count);
		cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i + 1), count));
		// t_cmd *cmd; // = parse(av[1]);
	}
		// print_fd_list(cmd);
	print_list(cmd);
	return (1);
}
//
// t_cmd *tmp;
// while (list)
// {
// 	tmp = list->next;
// 	int j = 0;
// 	while (list->av[j] != NULL)
// 	{
// 		printf("j : %d\n", j);
// 		free(list->av[j]);
// 		j++;
// 	}
// 	free(list->av);
// 	free(list);
// 	list = tmp;
// }
