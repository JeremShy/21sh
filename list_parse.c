/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/03 21:09:19 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

char	**split_cmd(char *str, size_t count)
{
	char		**av;
	size_t	i;
	size_t	tmp;

	av = malloc(count * sizeof(char*));
	str = NULL;
	i = 0;
	while (av[i])
	{
		while (ft_isspace2(av[i])) //On saute les espaces du début.
			i++;
		if (!ft_isspace2(av[i]) && av[i] != '\0')
		{
			count++;
			tmp = i;
			while (!ft_isspace2(av[i]) && av[i] != '\0')
			{
				if (av[i] == '|' || av[i] == ';')
				{
					*new_av = av + i;
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
	return (av);
}

t_cmd	*create_cmd_elem(char *str, size_t count)
{
	t_cmd		*elem;

	elem = (t_cmd*)malloc(sizeof(t_cmd));
	elem->av = split_cmd(str, count);
	elem->next = NULL;
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	if (list == NULL)
		return (elem);
	list->next = elem;
	return (elem);
}
