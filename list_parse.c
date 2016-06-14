/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 20:12:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/06/14 20:17:39 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		def_sep(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (DCHEV_DROITE);
	else if (ft_strnstr(str, "<<", 2))
		return (DCHEV_GAUCHE);
	else if (ft_strnstr(str, "&&", 2))
		return (ETET);
	else if (str[0] == '|')
		return (str[0]);
	else if (str[0] == '>')
		return (str[0]);
	else if (str[0] == '<')
		return (str[0]);
	else if (str[0] == ';')
		return(str[0]);
	return (0);
}

void		print_list(t_cmd *lst)
{
	size_t	i;
	char		**av;
	size_t	j;

	i = 0;
	while (lst != NULL)
	{
		printf("list number : %zu\n", i);
		av = lst->av;
		j = 0;
		while (av[j])
		{
			printf("av[%zu] : #%s#\n", j, av[j]);
			j++;
		}
		// printf("sep : %c\n", lst->sep);
		i++;
		print_fd_list(lst);
		lst = lst->next;
		printf("\n");
	}
}

t_cmd	*create_cmd_elem(char *str, int count)
{
	t_cmd		*elem;
	int			sep;

	sep = 0;
	elem = (t_cmd*)malloc(sizeof(t_cmd));
	elem->fd_in = create_fd(-1);
	elem->fd_out = create_fd(-1);
	elem->fd_err = create_fd(-1);
	printf("str : [%s]\n", str);
	elem->p_error	= 0;
	elem->error = 0;
	if (split_cmd(count, str, elem) == -1)
	{
		//faire quelque
		printf("ARGH\n");
		exit(0);
	}
	printf("on cree une liste.\n");
	elem->next = NULL;
	free(str);
	print_fd_list(elem);
	return (elem);
}

t_cmd *add_cmd_elem(t_cmd *list, t_cmd *elem)
{
	t_cmd *tmp;

	tmp = list;
	if (list == NULL)
		return (elem);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
	return (tmp);
}
