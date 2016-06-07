/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 19:25:53 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/07 17:31:24 by jcamhi           ###   ########.fr       */
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

int nb_arg(char *av, char **new_av, int *dchev)
{
	size_t	i;
	int			count;
	char		*suite;
	size_t	tmp;

	i = 0;
	count = 0;
	if (av[0] == '|')
	{
		ft_putstr_fd("21sh: parse error near '|'\n", 2);
		return (-1);
	}
	while (av[i])
	{
		while (ft_isspace2(av[i]))
			i++;
		if (!ft_isspace2(av[i]) && av[i] != '\0')
		{
			count++;
			tmp = i;
			while (!ft_isspace2(av[i]) && av[i] != '\0')
			{
				if (is_special(av + i, 0))
				{
					if (ft_strnstr(av + i, "&&", 2) || ft_strnstr(av + i, "<<", 2) || ft_strnstr(av + i, ">>", 2))
					{
						*dchev = 1;
						*new_av = av + i + 1;
					}
					else
					{
						*dchev = 0;
						*new_av = av + i;
					}
					return (tmp == i ? count - 1 : count);
				}
				if (is_quote_open(av[i]))
				{
					suite = pos_quote_end(av[i], av + i + 1);
					i = suite - av;
				}
				i++;
			}
		}
	}
	*new_av = av + i;
	return (count);
}

t_cmd		*parse(char	*str)
{
	int			count;
	char		*new_av;
	size_t	i;
	t_cmd		*list;
	int			dchev;

	list = NULL;
	i = 0;
	while (str[i])
	{
		count = nb_arg(str, &new_av, &dchev);
		if (count == -1)
			return(0);
		list = add_cmd_elem(list, create_cmd_elem(ft_strsub(str, 0, new_av - str + 1), count));
		str = new_av;
		if (str[0])
			str++;
	}
	return (list);
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
