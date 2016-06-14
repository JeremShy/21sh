/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 00:04:43 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	*pos_quote_end(char en_cours, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_quote_close(en_cours, str[i]))
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*quote_mgmt(char *str, int taille)
{
	char	*ret;

	ret = (char*)malloc(taille * sizeof(char));
	if (!ret)
		return(NULL);
	ft_strncpy(ret, str, taille - 1);
	ret[taille - 1] = '\0';
	printf("ret : %s\n", ret);
	return(ret);
}

int nb_arg(size_t *i, char *str, t_cmd *cmd)
{
	int			count;
	size_t 	tmp_i;
	char		*tmp;
	//char 		*sub_ret;

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
		printf("ACTUEL CHAR [%c] - *i = [%zu]\n", str[*i], *i);
		if(is_aggr(i, str, 1))
		{
			printf("IT'S ALIVE\n");
			// printf("i = %zu (current char = [%c])\n", *i, str[*i]);
		}
		else if (is_redir(i, str, 1, cmd))
		{
			printf("TYPICAL PENIS\n");
		}
		else if (is_sep(i, str, 1))
		{
			printf("RIP ORIGINALITE\n");
			// (*i)++;
			return (count);
		}
		else if ((tmp = skip_quotes_nb_arg(str, i, cmd)) != NULL)
		{
			printf("J'AIME LE CACA\n");
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
		// printf("%zu - [%c]\n", *i, str[*i]);
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
	t_cmd		fake_cmd;

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
		old_i = i;
		count = nb_arg(&i, str, &fake_cmd);
		// printf("str : %s\n", str + i);
		if (count == -1)
		{
			//free cmd.
			return(0);
		}
		printf("RESULTAT DE COUNT = [%d]\n", count);
		cmd = add_cmd_elem(cmd, create_cmd_elem(ft_strsub(str, old_i, i - old_i + 1), count));
		// t_cmd *cmd; // = parse(av[1]);
	}
		print_fd_list(cmd);
	// print_list(cmd);
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
